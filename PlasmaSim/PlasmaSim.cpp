
#include "pch.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
using namespace std;
#define e_charge 1.60217662e-19
#define e_mass 9.10938356e-31

int main()
{
	string str;
	ifstream input;
	ofstream log;
	ofstream output;

	input.open("input.txt");
	getline(input, str);
	regex match1("Distance in m = ");
	string tempstr = regex_replace(str, match1, "");
	double distance = stod(tempstr);
	getline(input, str);
	regex match2("Voltage in V = ");
	tempstr = regex_replace(str, match2, "");
	double Voltage = stod(tempstr);
	getline(input, str);
	regex match3("Total time in ns = ");
	tempstr = regex_replace(str, match3, "");
	double t = stod(tempstr)*1e-9;
	getline(input, str);
	regex match4("Time for a single pass in ns = ");
	tempstr = regex_replace(str, match4, "");
	double pas_t = stod(tempstr)*1e-9;
	getline(input, str);
	regex match5("Output rate = ");
	tempstr = regex_replace(str, match5, "");
	double out_rate = stod(tempstr);

	input.close();

	log.open("log.txt");
	log << "----------------------------------" << endl;
	log << "Distance read     " << distance << " m" << endl;
	log << "Voltage read      " << Voltage << " V" << endl;
	log << "Total time read   " << t << " s" << endl;
	log << "Pass time read    " << pas_t << " s" << endl;
	log << "Output rate read  " << out_rate << endl;
	log << "----------------------------------" << endl;

	double Efield = Voltage / distance;
	double EForce = e_charge * Efield;

	log << "Electric field    " << Efield << " V/m" << endl;
	log << "Electric Force    " << EForce << " m/s^2*kg" << endl;
	log << "Acceleration      " << EForce / e_mass << " m/s^2" << endl;
	log << "----------------------------------" << endl;

	struct particle {
		double pos_x;
		double vel_x;
		double acc_x;
	};
	particle e;
	e.pos_x = 0;
	e.vel_x = 0;
	e.acc_x = EForce / e_mass;

	output.open("output.txt");
	for (double i = 1; i < t*1e+9; i += pas_t * 1e+9)
	{
		e.pos_x += e.vel_x*pas_t + (e.acc_x*pas_t*pas_t) / 2;
		e.vel_x += e.acc_x*pas_t;
		if (fmod(i, out_rate) == 0)
		{
			output << std::defaultfloat << "pass " << i;
			output << std::scientific << "   x: " << e.pos_x << "    vel: " << e.vel_x << endl;
		}
	}
	output.close();
	log.close();
}
