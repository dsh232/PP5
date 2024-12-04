#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

std::string stringInput() {
	std::string name; 
	std::regex integer_expr("^[A-Z][a-z]{1,20}\\s[A-Z]\\.[A-Z]\\.$");
	
	while (true)
	{
		
		std::getline(std::cin, name);
		if (std::regex_match(name, integer_expr)) {
			return name;
		}
		else
		{
			std::cout << "enter name (example: Ivan I.I.): " ;
		}
	}
}
char charInput()       //проверка корректного ввода символов
{
	char input;
	while (!(std::cin >> input) || std::cin.peek() != '\n')
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Uncorrect input. " << std::endl;
	}
	return input;
}
double doubleInput()		//проверка на ввод.
{
	double input;
	while (!(std::cin >> input) //соответсвие введенного значения типу переменной
		|| std::cin.peek() != '\n')  //проверка на конец ввода
	{
		std::cin.clear();	//"лечим" поток. +состояние good
		while (std::cin.get() != '\n');
		std::cout << "Ucorrect input. Only numbers please. " << std::endl;
	}
	return input;
}
int intInput()		//проверка на ввод.
{
	int input;
	while (!(std::cin >> input) //соответсвие введенного значения типу переменной
		|| std::cin.peek() != '\n')  //проверка на конец ввода
	{
		std::cin.clear();	//"лечим" поток. +состояние good
		while (std::cin.get() != '\n');
		std::cout << "Uncorrect input. Only numbers please. " << std::endl;
	}
	return input;
}

class TempetureMeasure {
//1 
// 36.6 
// C
public:
	int count;
	double tempeture;
	char typeTemp;
	TempetureMeasure() : count(0), tempeture(0.0), typeTemp(' ') {}

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

	double getTempeture() {
		return tempeture;
	}
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

//шаблоны перегрузки оператора для вектора 
template < class T >
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
	{
		if (ii == v.begin()) 
			os << " " << *ii;
		else 
			os << " , " << *ii;
	}
	os << "]";
	return os;
}

template <class T>
std::istream& operator>>(std::istream& s, std::vector<T>& A) {
	while (true) {
		T x;
		char c = s.peek();

		if (c == '[' || c == ',') {
			s.ignore();
			if (s >> x) A.push_back(x);
			else throw std::invalid_argument(" ");
			continue;
		}

		if (c == ']') {
			s.ignore();
			return s;
		}

		/* Ignore line-break */
		s.ignore();
	}
	return s;
}

class Patient {
// Petrov I.I.
//	18
// 1 39.6 C
public:
	std::string namePatient;
	std::string surnamePatient;
	int age;
	std::vector<TempetureMeasure> tempMeasures;
	Patient() {}
	
	Patient(std::string newnamePatient, std::string newsurnamePatient, int newage, std::vector<TempetureMeasure> newtempMeasures) {
		namePatient = newnamePatient;
		surnamePatient = newsurnamePatient;
		age = newage;
		tempMeasures = newtempMeasures;
	}
	Patient(const Patient& c) {
		namePatient = c.namePatient;
		surnamePatient = c.surnamePatient;
		age = c.age;
		tempMeasures = c.tempMeasures;
	}
	~Patient(){
		tempMeasures.clear();
	}

	double getDrugs() {
		if (tempMeasures.size() > 0) {
			double lastTemp = tempMeasures.back().getTempeture();
			char typeTemp = tempMeasures.back().typeTemp;
			if (typeTemp == 'C' && lastTemp >= 38.0) { // Условие для Цельсия
				return age / 100.0 * (lastTemp - 36.6);
			}
			else if (typeTemp == 'F' && lastTemp >= 100.4) { // Условие для Фаренгейта
				return age / 100.0 * (lastTemp - 97.88);
			}
		}
		return 0; // Возвращаем 0, если условия не выполнены
	}

	friend std::ostream& operator<< (std::ostream&, const Patient&);
	friend std::istream& operator>> (std::istream&, Patient&);

};

std::ostream& operator<< (std::ostream& out, const Patient& c)
{
	out << c.namePatient << " " << c.surnamePatient << " " << c.age << " " << c.tempMeasures<< std::endl;
	return out;
}

// перегрузка оператора >>
std::istream& operator>> (std::istream& in, Patient& c)
{
	in >> c.namePatient >> c.surnamePatient  >> c.age >> c.tempMeasures;
	return in;
}

std::vector<std::string> explode(const std::string& delimiter, const std::string& str)
{
	std::vector<std::string> strings;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return strings;//no change

	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)//found delimiter
		{
			strings.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	strings.push_back(str.substr(k, i - k));
	return strings;
}


std::vector<Patient> patientInfo() {
	std::vector<Patient> patients;
	std::string name = "Ivan ";
	std::string surname = "I.I";

	for (int i = 0; i < 5; i++) {
		std::vector<TempetureMeasure> temps;
		for (int j = 0; j < 5; j++) {
			double tempp = 36.6 + (double(j) / 10);
			TempetureMeasure temp = TempetureMeasure(j, tempp, 'C');
			temps.push_back(temp);
		}
		name.append(std::to_string(i));
		Patient info = Patient(name, surname, 18 + i, temps);
		patients.push_back(info);
		std::cout << patients.at(i) << std::endl;
	}
	return patients;
}

std::vector<Patient> readConsole() {
	std::cout << "enter how many patients will be: ";
	std::vector<Patient> patients;
	int n = intInput();
	bool asking = true;
	for(int i = 0; i < n; i++) {
		std::vector<TempetureMeasure> temps;
		std::vector<std::string> fullname = explode(" ", stringInput());
		std::cout << "enter age of the patient: ";
		int age = intInput();
		if (age < 0) {
			while (asking) {
				std::cout << "enter age of the patient: ";
				age = intInput();
				if (age > 0) asking = false;
			}
		}
		asking = true;
		std::cout << "enter how many measure of temperature will be: ";
		int m = intInput();
		if (m < 0) {
			while (asking) {
				std::cout << "enter how many measure of temperature will be: ";
				m = intInput();
				if (m > 0) asking = false;
			}
		}
		std::cout << "What is the temperature in Faringate or Celsius? (F/C): ";
		char typeTemp = charInput();

		for (int j = 0; j < m; j++) {
			std::cout << "enter your " << j + 1 << " temperature: ";
			double tempp = doubleInput();
			TempetureMeasure temp = TempetureMeasure(j, tempp, typeTemp);
			temps.push_back(temp);
		}
		Patient info = Patient(fullname.front(), fullname.back(), age, temps);
        patients.push_back(info);
	}
	return patients;
}

void writeConsole(std::vector<Patient>& patients) {
	for (int i = 0; i < patients.size(); i++) {
		double dosage = patients[i].getDrugs();
		std::cout << "Patient: " << patients[i].namePatient << " " << patients[i].surnamePatient << ", Last Temperature: "
			<< patients[i].tempMeasures.back().getTempeture() << ", Age: "
			<< patients[i].age << ", Dosage: " << dosage << " mg." << std::endl;		
	}
}

std::vector<Patient> readFile() {
	std::vector<Patient> patients;
	std::ifstream inputFile("input.txt");
	
	if (inputFile.is_open())
	{
		inputFile >> patients;
	}
	else
	{
		std::cout << "file is not found.";
	}
	inputFile.clear();
	return patients;
}

void writeFile(std::vector<Patient> patients) {
	std::ofstream outputFile("output.txt");
	if (outputFile.is_open())
	{
		for (int i = 0; i < patients.size(); i++) {
			double dosage = patients[i].getDrugs();
			outputFile << "Patient: " << patients[i].namePatient << " " << patients[i].surnamePatient << ", Last Temperature: "
				<< patients[i].tempMeasures.back().getTempeture() << ", Age: "
				<< patients[i].age << ", Dosage: " << dosage << " mg." << std::endl;
		}
	}
	else
	{
		std::cout << "file is not found.";
	}
	outputFile.clear();
}

int main() {
	std::cout << "This program will help you choose the dosage of antipyretic based on your age and temperature. \n" << std::endl;
	bool answerContiune = true;
	std::vector<Patient> patients;
	std::cout << "how would you like to give us information? through console or file? (C/F): ";
	while (answerContiune) {
		char answer = charInput();
		if (answer == 'C') {
			patients = readConsole();
			answerContiune = false;
		}
		else if (answer == 'F') {
			patients = readFile();
			answerContiune = false;
		}
		else {
			std::cout << "uncorrect input. File or Console? ";
		}
	}
	answerContiune = true;
	std::cout << "where would you like us to write information? in console or in file? (C/F): ";
	while (answerContiune) {
		char answer = charInput();
		if (answer == 'C') {
			writeConsole(patients);
			answerContiune = false;
		}
		else if (answer == 'F') {
			writeFile(patients);
			answerContiune = false;
		}
		else {
			std::cout << "uncorrect input. File or Console? ";
		}
	}
}