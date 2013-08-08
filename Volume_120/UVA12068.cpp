#include <iostream>
#include <ostream>

using namespace std;

class Rational
{
    long long m_numer, m_denom;

    friend ostream & operator << (ostream & output, const Rational & obj);

    public:
        // Constructors
        Rational();
        Rational(long long numer, long long denom);
        Rational(long long numer);
        Rational(const Rational & other);
        // Deconstructor
        ~Rational();

        // Operator overloading
        Rational & operator = (const Rational & rhs);
        Rational & operator += (const Rational & rhs);
        Rational & operator -= (const Rational & rhs);
        Rational & operator *= (const Rational & rhs);
        Rational & operator /= (const Rational & rhs);
        const Rational operator + (const Rational & rhs) const;
        const Rational operator - (const Rational & rhs) const;
        const Rational operator * (const Rational & rhs) const;
        const Rational operator / (const Rational & rhs) const;
        bool operator == (const Rational & rhs) const;
        bool operator != (const Rational & rhs) const;
        bool operator >= (const Rational & rhs) const;
        bool operator > (const Rational & rhs) const;
        bool operator <= (const Rational & rhs) const;
        bool operator < (const Rational &rhs) const;

    private:
        void simplifyRational();
};

void Rational::simplifyRational()
{
    // Find the gcd of m_numer and m_denom
    long long copyNumer = m_numer, copyDenom = m_denom, temp;

    if(copyNumer < 0)
        copyNumer = -copyNumer;
    if(copyDenom < 0)
        copyDenom = -copyDenom;

    while(copyDenom != 0)
    {
        temp = copyNumer % copyDenom;
        copyNumer = copyDenom;
        copyDenom = temp;
    }

    // Divide both numerator and denominator by their GCD!
    if(copyNumer != 1)
    {
        m_numer /= copyNumer;
        m_denom /= copyNumer;
    }


    if(m_denom < 0)
    {
        m_denom = -m_denom;
        m_numer = -m_numer;
    }
}

Rational::Rational()
{
    // Create a zero rational number with numerator = 0 and denominator = 1
    m_numer = 0;
    m_denom = 1;
}

// Assumption: denom != 0
Rational::Rational(long long numer, long long denom)
{
    m_numer = numer;
    m_denom = denom;

    simplifyRational();
}

Rational::Rational(long long numer)
{
    m_numer = numer;
    m_denom = 1;
}

Rational::Rational(const Rational & other)
{
    m_numer = other.m_numer;
    m_denom = other.m_denom;
}

Rational::~Rational()
{
    return;     // Do nothing
}

Rational & Rational::operator = (const Rational & rhs)
{
    m_numer = rhs.m_numer;
    m_denom = rhs.m_denom;

    Rational & reference = *this;
    return reference;
}

Rational & Rational::operator += (const Rational & rhs)
{
    m_numer = m_numer * rhs.m_denom + m_denom * rhs.m_numer;
    m_denom *= rhs.m_denom;
    simplifyRational();

    Rational & reference = *this;
    return reference;
}

Rational & Rational::operator -= (const Rational & rhs)
{
    m_numer = m_numer * rhs.m_denom - m_denom * rhs.m_numer;
    m_denom *= rhs.m_denom;
    simplifyRational();

    Rational & reference = *this;
    return reference;
}

Rational & Rational::operator *= (const Rational & rhs)
{
    m_numer *= rhs.m_numer;
    m_denom *= rhs.m_denom;
    simplifyRational();

    Rational & reference = *this;
    return reference;
}

Rational & Rational::operator /= (const Rational & rhs)
{
    m_numer *= rhs.m_denom;
    m_denom *= rhs.m_numer;
    simplifyRational();

    Rational & reference = *this;
    return reference;
}

const Rational Rational::operator + (const Rational & rhs) const
{
    Rational result(*this);
    result += rhs;
    return result;
}

const Rational Rational::operator - (const Rational & rhs) const
{
    Rational result(*this);
    result -= rhs;
    return result;
}

const Rational Rational::operator * (const Rational & rhs) const
{
    Rational result(*this);
    result *= rhs;
    return result;
}

const Rational Rational::operator / (const Rational & rhs) const
{
    Rational result(*this);
    result /= rhs;
    return result;
}

bool Rational::operator == (const Rational & rhs) const
{
    // Note that rhs and this are in their simplest form and m_denome > 0
    if(m_numer == rhs.m_numer && m_denom == rhs.m_denom)
        return true;
    return false;
}

bool Rational::operator != (const Rational & rhs) const
{
    return !(*this == rhs);
}

bool Rational::operator > (const Rational &rhs) const
{
    Rational diff = (*this) - rhs;

    return diff.m_numer > 0;
}

bool Rational::operator >= (const Rational &rhs) const
{
    Rational diff = (*this) - rhs;

    return diff.m_numer >= 0;
}

bool Rational::operator < (const Rational &rhs) const
{
    Rational diff = (*this) - rhs;

    return diff.m_numer < 0;
}

bool Rational::operator <= (const Rational &rhs) const
{
    Rational diff = (*this) - rhs;

    return diff.m_numer <= 0;
}

ostream & operator << (ostream & output, const Rational & obj)
{
    output << obj.m_numer << "/" << obj.m_denom;
    return output;
}

Rational computeHarmonicMean(long long [], long long);

int main()
{
    int numTest, curCase;
    cin >> numTest;

    curCase = 1;
    while(curCase <= numTest)
    {
        long long numNum;
        cin >> numNum;
        long long arrNum[numNum];

        for(int index = 0; index < numNum; index++)
            cin >> arrNum[index];

        Rational result = computeHarmonicMean(arrNum, numNum);

        cout << "Case " << curCase << ": " << result << endl;

        curCase++;
    }

    return 0;
}

Rational computeHarmonicMean(long long arr[], long long num)
{
    // Create 0
    Rational result;

    for(int index = 0; index < num; index++)
        result += Rational(1, arr[index]);

    result = Rational(num) / result;

    return result;
}
