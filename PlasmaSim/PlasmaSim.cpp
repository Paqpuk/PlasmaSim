
#include "pch.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <vector>
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

double dEdx(double x);
double RG4(double t0, double t, double x, double h);
double declarecells(space $coo[arr], double cellsize, double length);
double tridag(double $Vn[arr], int length, struct space $coo[arr], double $cellsize);

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
	double Vn[length + 1];
	Vn[0] = V;
	Vn[length] = 0;

	tridag(Vn, length, coo, cellsize);

	for (int i = 0; i < length; i++)
	{
		coo[i].Efield = (Vn[i + 1] - Vn[i])/cellsize;
	}



	
	
	



	//e.pos_x = 0;
	//e.vel_x = 0;
	//double h = pas_t / 2;
	output.open("output.txt");

	for (int i = 0; i < length+1; i++)
	{
		output << i << " " << coo[i].Efield << " " << Vn[i] <<  endl;
	}

	//	e.vel_x = (e_charge / e_mass)*RG4(0, t, e.pos_x, pas_t);
	//	e.pos_x = e.vel_x * pas_t;
		

	//	output << std::scientific << "   x: " << e.pos_x << "    vel: " << e.vel_x << endl;

	output.close();
	simlog.close();
}

double dEdx(double x)
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
		k1 = h * dEdx(x);
		k2 = h * dEdx(x + 0.5*k1);
		k3 = h * dEdx(x + 0.5*k2);
		k4 = h * dEdx(x + k3);

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

double tridag(double $Vn[arr], int length, struct space $coo[arr], double $cellsize)
{
	vector<int> a, b, c;
	vector<double> r;
	double bet;

	for (int i = 0; i < length; i++)
		{
			a.push_back(1);
			b.push_back(-2);
			c.push_back(1);
			r.push_back(($coo[i].n_e - $coo[i].n_i)*(e_mass*$cellsize) / eps0);
			//cout << $coo[i].n_e << " - " << $coo[i].n_i << " * " << e_mass << " * " << $cellsize << " / " << eps0 << endl;
		}
		int j, n = a.size();
		vector<double> gam(n);
		$Vn[0] = r[0] / (bet = b[0]);
		//cout << r[0];	
		$Vn[0] = 500;
	for (j = 1; j < n; j++)
		{	
			//cout << j << endl;
			gam[j] = c[j - 1] / bet;
			//cout << gam[j] << " = " << c[j - 1] << " / " << bet << endl;
			bet = b[j] - a[j] * gam[j];
			//cout << bet << " = " << b[j] << " - " << a[j] << " * " << gam[j] << endl;
			$Vn[j] = (r[j] - a[j] * $Vn[j - 1]) / bet;
			//cout << $Vn[j] << " = (" << r[j] << " - " << a[j] << " * " << $Vn[j - 1] << ") / " << bet << "\n" << endl;
	}
	for (j = (n - 2); j >= 0; j--)
		{
			$Vn[j] -= gam[j + 1] * $Vn[j + 1];
			//cout << j << " " << $Vn[j] << endl;
		}
	return 0;
}