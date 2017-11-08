// ------------------------------------------------ Poly.h ---------------------
// Reza Naeemi CSS343 A
// Creation Date: 10/1/2016
// Date of Last Modification: 10/8/2015
// -----------------------------------------------------------------------------
// Purpose - To create an ADT (Abstract Data Type) of a polynomial
// -----------------------------------------------------------------------------
// Assumptions -
//
// - Only whole numbers used (int)
//
// Features -
//
// - Can multiply, Add and subtract a polynomial from another
// - Can Check for equality
// - Assignment operator and copy constructor
// - Uses a dynamically allocated array to hold coefficent
// -----------------------------------------------------------------------------


#include "Poly.h"

// ----------------------------------- <<operator ------------------------------
// Description: Initializes every element to a default 0 value
// -----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &output, const Poly &rightObj) 
{
    output << "";       // Start output with an empty string
    
    if (rightObj.coeffPtr != NULL)
    {
        // Enumerate through array in reverse order up to largestPower.
        // Do not output entire array when it is larger than the current
        // largestPower.
        for (int i = rightObj.largestPower; i >= 0; i--) 
        {
            
            // Only output coefficient if it is not 0.
            if (rightObj.coeffPtr[i] != 0) 
            {
                
                // Add a + sign to all positive coefficients,
                // with a space in front of it.
                if (rightObj.coeffPtr[i] > 0) 
                {
                    output << " +";
                }
                
                // Output current coefficient
                output << rightObj.coeffPtr[i];
                
                
                if (i > 0) 
                {
                    output << 'x';
                    
                    // Add a ^ sign after all x signs of coefficients
                    // that are in index greater than 1.
                    // Follow this with the current i to represent the power.
                    if (i > 1) 
                    {
                        output << '^' << i;
                    }
                    
                }
                
            }
            
        }
        
        // We should output 0, to represent an empty Polynomial.
        if (rightObj.arraySize == 0) 
        {
            output << " 0";
        }   
    }
    
    return output;      // Return the output
}

// ----------------------------------- operator>> ------------------------------
// Description: Initializes every element to a default 0 value
// -----------------------------------------------------------------------------
std::istream &operator >>(std::istream &input, Poly &rightObj)
{
    if (rightObj.coeffPtr != NULL)
    {
        delete[] rightObj.coeffPtr;
        rightObj.arraySize = 0;
        rightObj.largestPower = -1;
        rightObj.initializeArrayRange(rightObj.coeffPtr, 0, rightObj.arraySize);
    }
    
    
    int coefficient = 0;
    int power = 0;
    
    while (input >> coefficient >> power) // Inputs are entered
    {
        if ((coefficient == -1) && (power == -1))
        {
            return input;
        }
        
        if (input.fail())
        {
            return input;
        }
        
        
        rightObj.setCoeff(coefficient, power); 
        
    }
    
    return input;
    
}



// ------------------------------------createNewPoly----------------------------
// Description: Allocates a new array for the size needed,
// 		and then it returns a pointer to it to the 
//              caller of the function.
// -----------------------------------------------------------------------------
int* Poly::createNewPoly(int newArraySize) 
{
    return (new int[newArraySize]);
}


// ------------------------------------initializeArrayRange---------------------
// Description: Initializes every element of a range to a default 0 value
//		I am using range, so that I only write to those fields that will
//		end up with 0 in them. The other elements will be filled with the 
//                appropriate non-zero number. I am doing this to avoid writing 
//              to a the same element when I don't need to.
// -----------------------------------------------------------------------------
void Poly::initializeArrayRange(int* array, int begin, int end) 
{
    for (int i = begin; i <= end; i++)
    {
        array[i] = 0;
    }
}

// ------------------------------------grow-------------------------------------
// Description: grow is called when a larger array is needed in order to fit the
// 		Polynomial. The new array is created using the newLargestPower
//		Then, the all the elements will be copied over to the new array.
//		Finally, the old array will be deallocated and freed from memory.
// -----------------------------------------------------------------------------
void Poly::grow(int newLargestPower) 
{
    int newArraySize = newLargestPower + 1;
    int* newCoeffPtr = createNewPoly(newArraySize);
    
    if (coeffPtr != NULL)   // If coeffPtr is NULL, then no elements to copy over.
    {
        for (int i = 0; i < newLargestPower; i++)
        {
            newCoeffPtr[i] = coeffPtr[i];
        }
    }
    
    initializeArrayRange(newCoeffPtr, arraySize, newLargestPower);
    
    delete[] coeffPtr;
    coeffPtr = newCoeffPtr;
    newCoeffPtr = NULL;
    
    arraySize = newArraySize;
    largestPower = newLargestPower;
}

// ------------------------------------Poly-------------------------------------
// Description: Default Constructor
// -----------------------------------------------------------------------------
Poly::Poly() 
{
    largestPower = 0;
    arraySize = 1;
    
    coeffPtr = createNewPoly(arraySize);
    coeffPtr[largestPower] = 0;
}

// ------------------------------------Poly-------------------------------------
// Description: Constructor with 1 argument
// -----------------------------------------------------------------------------
Poly::Poly(int coefficient)
{
    arraySize = 2;
    largestPower = 1;
    
    coeffPtr = createNewPoly(arraySize);
    coeffPtr[largestPower] = coefficient;
    
}

// ------------------------------------Poly-------------------------------------
// Description: Constructor with 2 arguments
// 		Dynamically allocates maximum space needed
// 		Each array index correlates to an exponent
//              The value at the index correlates to its coefficient
// -----------------------------------------------------------------------------
Poly::Poly(int coefficient, int power) 
{
    arraySize = power + 1;
    largestPower = power;
    
    coeffPtr = createNewPoly(arraySize);
    coeffPtr[largestPower] = coefficient;
    
    if (power > 0) 
    {
        initializeArrayRange(coeffPtr, 0, power - 1);
    }
}

// ------------------------------------Poly-------------------------------------
// Description: Copy Constructor creates a deep copy using operator =.
// -----------------------------------------------------------------------------
Poly::Poly(const Poly& orig) 
{
    largestPower = orig.largestPower;
    arraySize = orig.arraySize;
    coeffPtr = createNewPoly(arraySize);
    
    for (int i = 0; i < arraySize; i++) 
    {
        coeffPtr[i] = orig.coeffPtr[i];
    }
}

// ------------------------------------~Poly------------------------------------
// Description: Destructor destroys dynamically allocated array
// -----------------------------------------------------------------------------
Poly::~Poly() 
{
    if (coeffPtr != NULL)
    {
        delete[] coeffPtr;
        coeffPtr = NULL;
        
        largestPower = 0;
        arraySize = 0;
    }
}

// ------------------------------------ operator -() ---------------------------
// Description: Negates every element in the a Poly object.
// Features:
//	- Negates every element in the Poly object.
//	- Adds each like term together
// -----------------------------------------------------------------------------
Poly &Poly::operator -()
{
	if (coeffPtr != NULL)
	{
		for (int i = 0; i <= largestPower; i++)
		{
			coeffPtr[i] *= -1;
		}
	}

    return *this;
}


// ------------------------------------ operator+ ------------------------------
// Description: Creates a Poly object and calls the operator+= thats already 
//              overloaded
// Precondition:
//	- operator+= overloaded
// Features:
//	- Creates an Array with the larger term arraySize
//	- Adds each like term together
// -----------------------------------------------------------------------------
Poly Poly::operator +(const Poly& rightObj) const
{
    Poly result(*this);
    result += rightObj;
    return result;
}

// ------------------------------------ operator- ------------------------------
// Description: Creates a Poly object and calls the operator-= thats already 
//                overloaded
// Precondition:
//	- operator-= overloaded
// Features:
//	- Creates an Array with the larger term arraySize
//	- Subtracts each like term together
// -----------------------------------------------------------------------------
Poly Poly::operator -(const Poly& rightObj) const
{
    Poly result(*this);
    result -= rightObj;
    return result;    
}

// ------------------------------------ operator* ------------------------------
// Description: Multiplies 2 poly. together and returns Poly reference
// Precondition:
//	- operator*= overloaded
// Features:
//	- Creates an Array with the size of the both lengths sumed
//	- Multipies each term together and places it in the larger array
// -----------------------------------------------------------------------------
Poly Poly::operator *(const Poly &rightObj) const
{
    Poly result(*this);
    result *= rightObj;
    return result;
}

// ------------------------------------ operator= ------------------------------
// Description: Creates a deep copy of the source Poly object,
//		but only allocates the the memory needed to store the
//		current Poly to the largest Power.
//		I am not entirely sure if this is the best route as far
//		as efficiency goes, but it makes sense to me to only allocate
//		for the resources needed, when using the Copy constructor.
// -----------------------------------------------------------------------------
Poly &Poly::operator =(const Poly& rightObj)
{
    if (*this != rightObj)
    {
        if (arraySize < rightObj.largestPower + 1)
        {
            delete[] coeffPtr;
            
            largestPower = rightObj.largestPower;
            arraySize = largestPower + 1;
            
            coeffPtr = createNewPoly(arraySize);
            
            for (int i = 0; i < arraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i];
            }
        }
    }
    
    return *this;
}

// ------------------------------------ operator+= -----------------------------
// Description: Adds 2 poly. together and returns Poly reference
// Precondition:
//	- Two Poly with at least 1 term
// Features:
//	- Creates an Array with the larger term arraySize
//	- Adds each like term together
// -----------------------------------------------------------------------------
Poly &Poly::operator +=(const Poly& rightObj)
{
    if (arraySize < rightObj.largestPower + 1)
    {
        int newArraySize = rightObj.largestPower + 1;
        
        if (coeffPtr != NULL)
        {
            int* tempCoeffPtr = coeffPtr;
            coeffPtr = createNewPoly(newArraySize);
            
            for (int i = 0; i < arraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i] + tempCoeffPtr[i];
            }
            
            for (int i = arraySize; i < newArraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i];
            }
        }
        else
        {
            coeffPtr = createNewPoly(newArraySize);

            for (int i = 0; i < arraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i];
            }
        }
        
        arraySize = newArraySize;
        largestPower = rightObj.largestPower;
    }
    else
    {
        for (int i = 0; i < rightObj.arraySize; i++)
        {
            coeffPtr[i] += rightObj.coeffPtr[i];
        }
    }
    
    return *this;
}

// ------------------------------------ operator-= -----------------------------
// Description: Subtracts 2 poly. together and returns Poly reference
// Precondition:
//	- Two Poly with at least 1 term
// Features:
//	- Creates an Array with the larger term arraySize
//	- Adds each like term together
// -----------------------------------------------------------------------------
Poly &Poly::operator -=(const Poly& rightObj)
{
    if (arraySize < rightObj.largestPower + 1)
    {
        int newArraySize = rightObj.largestPower + 1;
        
        if (coeffPtr != NULL)
        {
            int* tempCoeffPtr = coeffPtr;
            coeffPtr = createNewPoly(newArraySize);
            
            for (int i = 0; i < arraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i] - tempCoeffPtr[i];
            }
            
            for (int i = arraySize; i < newArraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i];
            }
        }
        else
        {
            coeffPtr = createNewPoly(newArraySize);

            for (int i = 0; i < arraySize; i++)
            {
                coeffPtr[i] = rightObj.coeffPtr[i];
            }
        }
        
        arraySize = newArraySize;
        largestPower = rightObj.largestPower;
    }
    else
    {
        for (int i = 0; i < rightObj.arraySize; i++)
        {
            coeffPtr[i] -= rightObj.coeffPtr[i];
        }
    }

    return *this;
}

// ------------------------------------ operator*= -----------------------------
// Description: Multiplies 2 poly. together and returns Poly reference
// Precondition:
//	- Two Poly with at least 1 term
// Features:
//	- Creates an Array with the size of the both lengths sumed
//	- Multipies each term together and places it in the larger array
// -----------------------------------------------------------------------------
Poly Poly::operator *=(const Poly& rightObj)
{
	// We need a temp array to hold the results.
	// The reason we can't just use the coeffPtr
	// like we do in + and - is because we most likely
	// will run into cases where as the coefficients
	// are being updated in the coeffPtr,
	// our math will use the new updated value to
	// calculate the rest of the coefficents.
	// Note: This is no different than us asking someone
	// a question and then before they have a chance to 
	// give us an answer, our question has already changed.
	// So, there answer to my new question will most likely
	// be wrong!
    Poly result(
        (coeffPtr[largestPower] * rightObj.coeffPtr[rightObj.largestPower]),
        (largestPower + rightObj.largestPower));

    for (int i = 0; i <= largestPower; i++)
    {
        for (int j = 0; j <= rightObj.largestPower; j++)
        {
            result.coeffPtr[i + j] += (coeffPtr[i] * rightObj.coeffPtr[j]);
        }
    }

    return result;    
}

// ------------------------------------ operator== -----------------------------
// Description: Compares both sides to see if they are considered equal.
//		Note: As long as the Polynomials are the same,
//		we will consider them the same.
//              This means that we don't care if the size of the arrays
//              are different.
// -----------------------------------------------------------------------------
bool Poly::operator ==(const Poly &rightObj) const
{
    if (largestPower != rightObj.largestPower)
    {
	return false;
    }

    for (int i = 0; i <= largestPower; i++)
    {
        if (coeffPtr[i] != rightObj.coeffPtr[i])
        {
            return false;
        }
    }

    // If we get here, the Poly objects are considered equal.
    // We consider Poly objects equal, even if they don't have the same array size.
    // As long as the elements and the largestPower are the same, 
    // we consider them to be equal Polynomials.
    return true;
}

// ------------------------------------ operator!= -----------------------------
// Description: The opposite of the ==operator.
//	Precondition: The ==operator must be implemented for this to work,
//		since we are considering the opposite to be a true condition for 
//              this function.
// -----------------------------------------------------------------------------

bool Poly::operator !=(const Poly &rightObj) const
{
    return !
        (*this == rightObj);
}

// ------------------------------------getCoeff---------------------------------
// Description: Accessor that returns the coeffienct of a given exponent
// Precondition: int argument passed in representing the exponent
// Features: Returns the coffienct of that exponent
//				If value is out of range, return 0.
// -----------------------------------------------------------------------------
int Poly::getCoeff(int power) const
{
    if ((power <= largestPower) && (power >= 0))
    {
        return coeffPtr[power];
    }
    
    return 0;  
}

// ------------------------------------setCoeff---------------------------------
// Description: Mutator that sets the coefficient of a given exponent
// Precondition:
//	- int argument passed in representing the coefficient & exponent
// Features:
//	- sets the coefficient in the array of coeffPtr of a given exponent(index)
// -----------------------------------------------------------------------------
bool Poly::setCoeff(int coefficient, int power)
{
    if (power < 0)
    {
        coefficient = 0;
        power = 1;
    }
    
    
    if ((arraySize < (power + 1)))  // If there is NOT enough room in current Array
    {
         grow(power);     
    }
    
    // Now assign the coefficient coeffPtr[power] element.
    coeffPtr[power] = coefficient;
    
    return true;
}


