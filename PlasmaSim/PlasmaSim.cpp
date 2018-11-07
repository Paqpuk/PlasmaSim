
#include "pch.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <time.h>
	using namespace std;
		#define e_charge 1.60217662e-19
		#define e_mass 9.10938356e-31
		#define arr 10000000
		#define eps0 8.854e-12

	struct space {
		double n_i;
		double n_e;
		double V;
		double Efield;
		double pos;
	};

double dVdx(double x);
double RG4(double t0, double t, double x, double h);
double declarecells(space $coo[arr], double cellsize, double length);
double declarepot(double $V1[arr], double length, double V);

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

			const int length = 1000;
			double cellsize = 0.01;

	struct particle {
		double pos_x;
		double vel_x;
	};

	space coo[length];
	declarecells(coo, cellsize, length);

	double V = 500;
	double V1[length + 1];
	declarepot(V1, length + 1, V);

	for (int i = 0; i < length; i++)
	{
		coo[i].V = (((e_charge*0.01*0.01) / eps0)*(coo[i].n_i - coo[i].n_e) + V1[i] + V1[i + 1]) / 2;
	}

	
	
	



	//e.pos_x = 0;
	//e.vel_x = 0;
	//double h = pas_t / 2;
	output.open("output.txt");

	for (int i = 0; i < length; i++)
	{
		output << i+1 << " " << coo[i].pos << "  " << coo[i].n_i << " | " << coo[i].n_e << endl;
	}

	//	e.vel_x = (e_charge / e_mass)*RG4(0, t, e.pos_x, pas_t);
	//	e.pos_x = e.vel_x * pas_t;
		

	//	output << std::scientific << "   x: " << e.pos_x << "    vel: " << e.vel_x << endl;

	output.close();
	simlog.close();
}

double dVdx(double x)
{
	return 0;
}

double RG4(double t0, double t, double x0, double h)
{
	int n = (int)((t - t0) / h);

	double k1, k2, k3, k4;
 
	double x = x0;
	for (int i = 1; i <= n; i++)
	{
		k1 = h * dVdx(x);
		k2 = h * dVdx(x + 0.5*k1);
		k3 = h * dVdx(x + 0.5*k2);
		k4 = h * dVdx(x + k3);

		x += + (1.0 / 6.0)*(k1 + 2 * k2 + 2 * k3 + k4);;

	}

	return x;
}

double declarecells(struct space $coo[arr], double cellsize, double length)
{
	for (int i = 0; i < length; i++)
	{
		//srand(time(NULL));
		$coo[i].pos = i * cellsize;
		$coo[i].n_e = (double(rand() % 101))/100;
		$coo[i].n_i = 1 - $coo[i].n_e;
	}
	return 0;
}

double declarepot(double $V1[arr], double length, double V)
{
	for (int i = 0; i < length; i++)
	{
		$V1[i] = (V / length)*i;
	}
	return 0;
}