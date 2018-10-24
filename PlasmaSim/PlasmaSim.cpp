
#include "pch.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
#include <math.h>
#include <stdio.h>
	using namespace std;
		#define e_charge 1.60217662e-19
		#define e_mass 9.10938356e-31

double Edxdt(double x);
double RG4(double t0, double t, double x, double h);



int main()
{
	string str;
	ifstream input;
	ofstream simlog;
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

		simlog.open("simlog.txt");
			simlog << "----------------------------------" << endl;
			simlog << "Distance read     " << distance << " m" << endl;
			simlog << "Voltage read      " << Voltage << " V" << endl;
			simlog << "Total time read   " << t << " s" << endl;
			simlog << "Pass time read    " << pas_t << " s" << endl;
			simlog << "Output rate read  " << out_rate << endl;
			simlog << "----------------------------------" << endl;


	struct particle {
		double pos_x;
		double vel_x;
	};
	particle e;
	
	
	



	e.pos_x = 0;
	e.vel_x = 0;
	double h = pas_t / 2;
	output.open("output.txt");

		e.vel_x = (e_charge / e_mass)*RG4(0, t, e.pos_x, pas_t);
		e.pos_x = e.vel_x * pas_t;
		

		output << std::scientific << "   x: " << e.pos_x << "    vel: " << e.vel_x << endl;

	output.close();
	simlog.close();
}

double Edxdt(double x)
{
	return (cos(x)+1);
}

double RG4(double t0, double t, double x0, double h)
{
	int n = (int)((t - t0) / h);

	double k1, k2, k3, k4, k5;
 
	double x = x0;
	for (int i = 1; i <= n; i++)
	{
		k1 = h * Edxdt(x);
		k2 = h * Edxdt(x + 0.5*k1);
		k3 = h * Edxdt(x + 0.5*k2);
		k4 = h * Edxdt(x + k3);

		x += + (1.0 / 6.0)*(k1 + 2 * k2 + 2 * k3 + k4);;

	}

	return x;
}