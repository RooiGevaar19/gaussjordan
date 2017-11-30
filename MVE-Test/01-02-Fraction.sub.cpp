// klasa Ułamek

class Fraction {
	private:
		// Fraction parts
		long long numerator, denominator;
		// GCD
		long long euclidean(long long num1, long long num2) {
			while ( num1 != num2 && num1 > 0 && num2 > 0 ) (( num1 > num2 ) ? (num1-=num2) : (num2-=num1));
    		return (num1>0) ? num1 : num2;
		}
	public:
		// konstruktor
		Fraction(void) {
			this->numerator = 0;
			this->denominator = 0;
		}
		Fraction(double Number) {
			this->convertDoubleToFraction(Number);
		}
		Fraction(int a) {
			this->numerator = a;
			this->denominator = 1;
		}
		// destruktor
		~Fraction(void) {

		}

		// Getter i Setter
		long long getNumerator(void) {
			return this->numerator;
		}
		long long getDenominator(void) {
			return this->denominator;
		}
		void setNumerator(long long x) {
			this->numerator = x;
		}
		void setDenominator(long long x) {
			this->denominator = x;
		}

		// funkcje ułamkowe
		bool reduce(void) {
			long long gcd = this->euclidean(this->numerator, this->denominator);
			if (1 < gcd) {
				this->numerator /= gcd;
				this->denominator /= gcd;

				return true;
			} else {
				return false;
			}
		}
		void convertDoubleToFraction(double Number) {
			this->denominator = 1;
			while(((double)(int)Number) != Number) {
				Number = Number * 10;
				this->denominator = this->denominator * 10;
			}
			this->numerator = (long long)Number;
			this->reduce();
		}
		double convertFractionToDouble(void) {
			return (double)this->numerator / (double)this->denominator;
		}

		// Operator overloading functions
		bool operator<(Fraction fraction) {
			return (this->numerator * (this->denominator * fraction.getDenominator())) < (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
		}
		bool operator<=(Fraction fraction) {
			return (this->numerator * (this->denominator * fraction.getDenominator())) <= (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
		}
		bool operator>(Fraction fraction) {
			return (this->numerator * (this->denominator * fraction.getDenominator())) > (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
		}
		bool operator>=(Fraction fraction) {
			return (this->numerator * (this->denominator * fraction.getDenominator())) >= (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
		}
		bool operator==(Fraction fraction) {
			return (this->numerator * (this->denominator * fraction.getDenominator())) == (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
		}
		bool operator!=(Fraction fraction) {
			return (this->numerator * (this->denominator * fraction.getDenominator())) != (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
		}
		long long operator%(Fraction fraction) {
			long long result;
			result = ((this->numerator * fraction.getDenominator()) % (this->denominator * fraction.getNumerator())) / (this->denominator * fraction.getDenominator());
			return result;
		}
		operator double() {
			return this->convertFractionToDouble();
		}
		operator float() {
			return (float)this->convertFractionToDouble();
		}
		operator long() {
			return (long)this->convertFractionToDouble();
		}
		operator long long() {
			return (long long)this->convertFractionToDouble();
		}
		operator string() {
			stringstream output;
			output << this->getNumerator() << "/" << this->getDenominator();
			return output.str();
		}

		Fraction operator=(Fraction pom) {
            if (&pom == this) return *this;
            this->numerator = pom.getNumerator();
            this->denominator = pom.getDenominator();
            return *this;
        }

		Fraction operator+(Fraction fraction) {
			Fraction resultFraction;

			if (this->denominator == fraction.getDenominator()) {
				resultFraction.setNumerator(this->numerator + fraction.getNumerator());
				resultFraction.setDenominator(this->denominator);
			} else {
				resultFraction.setNumerator((this->numerator * fraction.getDenominator()) + (fraction.getNumerator() * this->denominator));
				resultFraction.setDenominator(this->denominator * fraction.getDenominator());
			}

			return resultFraction;
		}
		Fraction operator+=(Fraction fraction) {
			if (this->denominator == fraction.getDenominator()) {
				this->numerator += fraction.getNumerator();
			} else {
				this->numerator = (this->numerator * fraction.getDenominator()) + (fraction.getNumerator() * this->denominator);
				this->denominator *= fraction.getDenominator();
			}
			return *this;
		}
		Fraction operator-=(Fraction fraction) {
			if (this->denominator == fraction.getDenominator()) {
				this->numerator -= fraction.getNumerator();
			} else {
				this->numerator = (this->numerator * fraction.getDenominator()) - (fraction.getNumerator() * this->denominator);
				this->denominator *= fraction.getDenominator();
			}
			return *this;
		}
		Fraction operator-(Fraction fraction) {
			Fraction resultFraction;

			if (this->denominator == fraction.getDenominator()) {
				resultFraction.setNumerator(this->numerator - fraction.getNumerator());
				resultFraction.setDenominator(this->denominator);
			} else {
				resultFraction.setNumerator((this->numerator * fraction.getDenominator()) - (fraction.getNumerator() * this->denominator));
				resultFraction.setDenominator(this->denominator * fraction.getDenominator());
			}

			return resultFraction;
		}
		Fraction operator*(Fraction fraction) {
			Fraction resultFraction;
			resultFraction.setNumerator(this->numerator * fraction.getNumerator());
			resultFraction.setDenominator(this->denominator * fraction.getDenominator());
			return resultFraction;
		}
		Fraction operator*=(Fraction fraction) {
			this->denominator *= fraction.getDenominator();
			this->numerator *= fraction.getNumerator();
			return *this;
		}
		Fraction operator/(Fraction fraction) {
			Fraction resultFraction;
			resultFraction.setDenominator(this->denominator * fraction.getNumerator());
			resultFraction.setNumerator(this->numerator * fraction.getDenominator());
			return resultFraction;
		}
		Fraction operator/(int fraction) {
			Fraction resultFraction;
			resultFraction.setDenominator(this->denominator);
			resultFraction.setNumerator(this->numerator * fraction);
			return resultFraction;
		}
		Fraction operator/=(Fraction fraction) {
			this->denominator *= fraction.getNumerator();
			this->numerator *= fraction.getDenominator();
			return *this;
		}
		Fraction operator~(void) {
			Fraction resultFraction;
			if (this->numerator > this->denominator) {
				return *this;
			} else {
				resultFraction.setNumerator(this->denominator - this->numerator);
				resultFraction.setDenominator(this->denominator);
				return resultFraction;
			}
		}
		Fraction operator++(void) {
			this->numerator += 1*(this->denominator);
			return *this;
		}
		Fraction operator--(void) {
			this->numerator -= 1*(this->denominator);
			return *this;
		}
		Fraction operator-() {
			this->numerator *= -1;
			return *this;
		}
};
