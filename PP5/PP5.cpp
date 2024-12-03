#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//шаблоны перегрузки оператора для вектора 
template < class T >
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
	{
		os << " " << *ii;
	}
	os << "]";
	return os;
}

template <class T>
std::istream& operator>>(std::istream& s, std::vector<T>& A)
{
	T x;
	string token; char blank;

	s >> blank; // Gobble the first '['
	while (getline(s, token, ','))
	{
		istringstream input(token);
		input >> x;
		A.push_back(x);
	}
	// s >> blank; // Gobble the last ']'
	return s;
}

class TempetureMeasure {
//1 
// 36.6 
// C
private:
	int count;
	double tempeture;
	char typeTemp;
public: 
	

	TempetureMeasure() {

	}

	TempetureMeasure(int newcount, double newtempeture, char newtypetemp) { 
		count = newcount;
		tempeture = newtempeture;
		typeTemp = newtypetemp;
	}

	TempetureMeasure(const TempetureMeasure& c) {
		count = c.count;
		tempeture = c.tempeture;
		typeTemp = c.typeTemp;
	}

	~TempetureMeasure() {}


  friend std::ostream & operator<< (std::ostream &, const TempetureMeasure&);
  friend std::istream & operator>> (std::istream &, TempetureMeasure&);

};


// перегрузка оператора <<
std::ostream& operator<< (std::ostream& out, const TempetureMeasure& c)
{
  out << c.count << " " << c.tempeture << " " << c.typeTemp;
  return out;
}


// перегрузка оператора >>
std::istream& operator>> (std::istream &in, TempetureMeasure& c)
{
  in >> c.count >> c.tempeture >> c.typeTemp;
  return in;
}


class Patient {
// Petrov I.I.
//	18
// 1 39.6 C
private:
	std::string namePatient;
	int age;
	std::vector<TempetureMeasure> tempMeasures;
public:
	
	Patient() {

	}

	Patient(std::string newnamePatient, int newage, std::vector<TempetureMeasure> newtempMeasures) {
		namePatient = newnamePatient;
		age = newage;
		tempMeasures = newtempMeasures;
	}
	Patient(const Patient& c) {
		namePatient = c.namePatient;
		age = c.age;
		tempMeasures = c.tempMeasures;
	}
	~Patient(){
		tempMeasures.clear();
	}
	friend std::ostream& operator<< (std::ostream&, const Patient&);
	friend std::istream& operator>> (std::istream&, Patient&);

};

std::ostream& operator<< (std::ostream& out, const Patient& c)
{
	out << c.namePatient << " " << c.age << " " << c.tempMeasures;
	return out;
}

// перегрузка оператора >>
std::istream& operator>> (std::istream& in, Patient& c)
{
	in >> c.namePatient >> c.age >> c.tempMeasures;
	return in;
}

int main() {

}