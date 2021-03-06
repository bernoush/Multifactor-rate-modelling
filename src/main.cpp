#include <iostream>

#include <vector>
#include <cmath>
#include <stdlib.h>

#include "HW1.h"
#include "CallZC.h"
#include "MonteCarlo.h"
#include <Eigen/Dense>
#include "Math.h"

#include <algorithm> // max_element, min_element
#include <vector>

using namespace std;
using Eigen::MatrixXd;


int main()
{
	int last_year = 30;
	int step = 2;

	HW1 *hjm = new HW1(0.5, 0.2);

	vector<double> term_structure_ = hjm->term_structure_hw1(last_year, step);


	vector<double> initial_forward_rate_ = hjm->initial_forward_rate(term_structure_);
	vector<double> initial_zero_coupon_ = hjm->initial_zero_coupon(initial_forward_rate_, term_structure_);


	vector<double> mvt_brownian = hjm->vector_movement_brownien(term_structure_);

	//vector<double> short_rate = hjm->short_rate_hw1(mvt_brownian, term_structure_);

	//double forward_rate = hjm->forward_rate_hw1(1, last_year, mvt_brownian, term_structure_);

	double zc = hjm->zero_coupon_bonds_hw1(1, last_year, mvt_brownian, term_structure_);

	CallZC *call_zc = new CallZC(hjm, last_year, 5, 0.0003);

	MonteCarlo *mc = new MonteCarlo(hjm, call_zc, 500, last_year, step);


	double price = mc->price();
    double price_theory=call_zc->price_theory_CallZC(term_structure_,initial_zero_coupon_);
	cout << "this is the price " << price_theory << endl;



	return 0;
}
