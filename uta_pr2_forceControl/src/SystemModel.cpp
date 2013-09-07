/*
 * SystemModel.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: Isura
 */

#include "SystemModel.h"

SystemModel::SystemModel( double m, double d, double k )
{
	// TODO Auto-generated constructor stub
	Mm    = Eigen::Matrix<double, Joints, Joints>::Identity()*m;
	Dm    = Eigen::Matrix<double, Joints, Joints>::Identity()*d;
	Km    = Eigen::Matrix<double, Joints, Joints>::Identity()*k;

	q_m   = Eigen::Matrix<double, Joints, 1>::Zero();
	qd_m  = Eigen::Matrix<double, Joints, 1>::Zero();
	qdd_m = Eigen::Matrix<double, Joints, 1>::Zero();

	t_h   = Eigen::Matrix<double, Joints, 1>::Zero();

	MmInv = Mm;

	delT  = 0.001;

}

SystemModel::~SystemModel()
{
	// TODO Auto-generated destructor stub
}

void SystemModel::update( KDL::JntArray & tau_human )
{
	t_h(0) = tau_human(0);
	t_h(1) = tau_human(1);
	t_h(2) = tau_human(2);
	t_h(3) = tau_human(3);
	t_h(4) = tau_human(4);
	t_h(5) = tau_human(5);
	t_h(6) = tau_human(6);

	q_m   = delT*qd_m;
	qd_m  = delT*qdd_m;
	qdd_m = MmInv*( t_h - Dm*qd_m - Km*q_m );
}

//void SystemModel::getStates( KDL::JntArray & q_m_, KDL::JntArray & qd_m_, KDL::JntArray & qdd_m_ )
//{
//	q_m_(0)   = q_m(0);
//	q_m_(1)   = q_m(1);
//	q_m_(2)   = q_m(2);
//	q_m_(3)   = q_m(3);
//	q_m_(4)   = q_m(4);
//	q_m_(5)   = q_m(5);
//	q_m_(6)   = q_m(6);
//
//	qd_m_(0)  = qd_m(0);
//	qd_m_(1)  = qd_m(1);
//	qd_m_(2)  = qd_m(2);
//	qd_m_(3)  = qd_m(3);
//	qd_m_(4)  = qd_m(4);
//	qd_m_(5)  = qd_m(5);
//	qd_m_(6)  = qd_m(6);
//
//	qdd_m_(0) = qdd_m(0);
//	qdd_m_(1) = qdd_m(1);
//	qdd_m_(2) = qdd_m(2);
//	qdd_m_(3) = qdd_m(3);
//	qdd_m_(4) = qdd_m(4);
//	qdd_m_(5) = qdd_m(5);
//	qdd_m_(6) = qdd_m(6);
//}
