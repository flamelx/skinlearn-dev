/*
 * outer_loop.h
 *
 *  Created on: Jan 22, 2014
 *      Author: isura
 */

#ifndef RLS_OUTER_LOOP_H_
#define RLS_OUTER_LOOP_H_

#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>
#include <Eigen/Core>

#include "oel/least_squares.hpp"

// TODO take this inside class
typedef boost::array<double, 21> state_type;

void mass_spring_damper_model( const state_type &x , state_type &dxdt , double t )
{
      double m = 1;
      double d = 10;
      double k = 1;

      dxdt[0 ] = x[7 ];
      dxdt[1 ] = x[8 ];
      dxdt[2 ] = x[9 ];
      dxdt[3 ] = x[10];
      dxdt[4 ] = x[11];
      dxdt[5 ] = x[12];
      dxdt[6 ] = x[13];

      //             f_r               qd_m      q_m
      dxdt[7 ] = m*( x[14] - d*x[7 ] - k*x[0 ] );
      dxdt[8 ] = m*( x[15] - d*x[8 ] - k*x[1 ] );
      dxdt[9 ] = m*( x[16] - d*x[9 ] - k*x[2 ] );
      dxdt[10] = m*( x[17] - d*x[10] - k*x[3 ] );
      dxdt[11] = m*( x[18] - d*x[11] - k*x[4 ] );
      dxdt[12] = m*( x[19] - d*x[12] - k*x[5 ] );
      dxdt[13] = m*( x[20] - d*x[13] - k*x[6 ] );

      dxdt[14] = 0 ;
      dxdt[15] = 0 ;
      dxdt[16] = 0 ;
      dxdt[17] = 0 ;
      dxdt[18] = 0 ;
      dxdt[19] = 0 ;
      dxdt[20] = 0 ;
}

void task_model( const state_type &x , state_type &dxdt , double t )
{
      double a = 10;
      double m = a*a;
      double d = 2*a;
      double k = a*a;

      dxdt[0 ] = x[7 ];
      dxdt[1 ] = x[8 ];
      dxdt[2 ] = x[9 ];
      dxdt[3 ] = x[10];
      dxdt[4 ] = x[11];
      dxdt[5 ] = x[12];
      dxdt[6 ] = x[13];

      //             f_r               qd_m      q_m
      dxdt[7 ] = m*( x[14] - d*x[7 ] - k*x[0 ] );
      dxdt[8 ] = m*( x[15] - d*x[8 ] - k*x[1 ] );
      dxdt[9 ] = m*( x[16] - d*x[9 ] - k*x[2 ] );
      dxdt[10] = m*( x[17] - d*x[10] - k*x[3 ] );
      dxdt[11] = m*( x[18] - d*x[11] - k*x[4 ] );
      dxdt[12] = m*( x[19] - d*x[12] - k*x[5 ] );
      dxdt[13] = m*( x[20] - d*x[13] - k*x[6 ] );

      dxdt[14] = 0 ;
      dxdt[15] = 0 ;
      dxdt[16] = 0 ;
      dxdt[17] = 0 ;
      dxdt[18] = 0 ;
      dxdt[19] = 0 ;
      dxdt[20] = 0 ;
}

namespace csl
{

namespace outer_loop
{

class MsdModel
{

  double num_Joints; // number of joints.

  Eigen::MatrixXd Mm;
  Eigen::MatrixXd Dm;
  Eigen::MatrixXd Km;
  Eigen::MatrixXd MmInv;

  Eigen::MatrixXd q;
  Eigen::MatrixXd qd;
  Eigen::MatrixXd qdd;

  Eigen::MatrixXd q_m;
  Eigen::MatrixXd qd_m;
  Eigen::MatrixXd qdd_m;
  Eigen::MatrixXd t_r;

  double delT; // Time step

  double m ;
  double d ;
  double k ;

  state_type ode_init_x;


public:
  MsdModel()
  {
    num_Joints = 7;
    delT = 0.001; /// 1000 Hz by default

    init( 1, 10, 1 );
  }
  ~MsdModel()
  {
  }

  void changeModelstructure(double para_num_Joints)
  {
    num_Joints = para_num_Joints;
  }

  void init( double p_m, double p_d, double p_k)
  {
    m = p_m;
    d = p_d;
    k = p_k;

    Mm    .resize( num_Joints, num_Joints ) ;
    Dm    .resize( num_Joints, num_Joints ) ;
    Km    .resize( num_Joints, num_Joints ) ;
    MmInv .resize( num_Joints, num_Joints ) ;

    q     .resize( num_Joints, 1 ) ;
    qd    .resize( num_Joints, 1 ) ;
    qdd   .resize( num_Joints, 1 ) ;

    q_m   .resize( num_Joints, 1 ) ;
    qd_m  .resize( num_Joints, 1 ) ;
    qdd_m .resize( num_Joints, 1 ) ;
    t_r   .resize( num_Joints, 1 ) ;

    Mm << m, 0, 0, 0, 0, 0, 0,
         0, m, 0, 0, 0, 0, 0,
         0, 0, m, 0, 0, 0, 0,
         0, 0, 0, m, 0, 0, 0,
         0, 0, 0, 0, m, 0, 0,
         0, 0, 0, 0, 0, m, 0,
         0, 0, 0, 0, 0, 0, m;

    Dm << d, 0, 0, 0, 0, 0, 0,
         0, d, 0, 0, 0, 0, 0,
         0, 0, d, 0, 0, 0, 0,
         0, 0, 0, d, 0, 0, 0,
         0, 0, 0, 0, d, 0, 0,
         0, 0, 0, 0, 0, d, 0,
         0, 0, 0, 0, 0, 0, d;

    Km << k, 0, 0, 0, 0, 0, 0,
         0, k, 0, 0, 0, 0, 0,
         0, 0, k, 0, 0, 0, 0,
         0, 0, 0, k, 0, 0, 0,
         0, 0, 0, 0, k, 0, 0,
         0, 0, 0, 0, 0, k, 0,
         0, 0, 0, 0, 0, 0, k;

    q_m   << 0, 0, 0, 0, 0, 0, 0 ;
    qd_m  << 0, 0, 0, 0, 0, 0, 0 ;
    qdd_m << 0, 0, 0, 0, 0, 0, 0 ;

    t_r   << 0, 0, 0, 0, 0, 0, 0 ;

    MmInv = Mm;

    // initial conditions
    ode_init_x[0 ] = 0.0;
    ode_init_x[1 ] = 0.0;
    ode_init_x[2 ] = 0.0;
    ode_init_x[3 ] = 0.0;
    ode_init_x[4 ] = 0.0;
    ode_init_x[5 ] = 0.0;
    ode_init_x[6 ] = 0.0;

    ode_init_x[7 ] = 0.0;
    ode_init_x[8 ] = 0.0;
    ode_init_x[9 ] = 0.0;
    ode_init_x[10] = 0.0;
    ode_init_x[11] = 0.0;
    ode_init_x[12] = 0.0;
    ode_init_x[13] = 0.0;

    ode_init_x[14] = 0.0;
    ode_init_x[15] = 0.0;
    ode_init_x[16] = 0.0;
    ode_init_x[17] = 0.0;
    ode_init_x[18] = 0.0;
    ode_init_x[19] = 0.0;
    ode_init_x[20] = 0.0;
  }

  void updateDelT(double p_delT)
  {
    delT = p_delT;
  }

  Eigen::MatrixXd getMass()
  {
    return Mm;
  }

  Eigen::MatrixXd getSpring()
  {
    return Km;
  }

  Eigen::MatrixXd getDamper()
  {
    return Dm;
  }

  void Update( Eigen::MatrixXd & qd_m  ,
               Eigen::MatrixXd & qd    ,
               Eigen::MatrixXd & q_m   ,
               Eigen::MatrixXd & q     ,
               Eigen::MatrixXd & qdd_m ,
               Eigen::MatrixXd & t_r    )
  {

//      q_m   = q_m + delT*qd_m;
//      qd_m  = qd_m + delT*qdd_m;
//      qdd_m = MmInv*( t_r - Dm*qd_m - Km*q_m );

      ode_init_x[14] = t_r(0);
      ode_init_x[15] = t_r(1);
      ode_init_x[16] = t_r(2);
      ode_init_x[17] = t_r(3);
      ode_init_x[18] = t_r(4);
      ode_init_x[19] = t_r(5);
      ode_init_x[20] = t_r(6);

      boost::numeric::odeint::integrate( mass_spring_damper_model , ode_init_x , 0.0 , delT , delT );

      q_m(0)   = ode_init_x[0 ] ;
      q_m(1)   = ode_init_x[1 ] ;
      q_m(2)   = ode_init_x[2 ] ;
      q_m(3)   = ode_init_x[3 ] ;
      q_m(4)   = ode_init_x[4 ] ;
      q_m(5)   = ode_init_x[5 ] ;
      q_m(6)   = ode_init_x[6 ] ;

      qd_m(0)  = ode_init_x[7 ] ;
      qd_m(1)  = ode_init_x[8 ] ;
      qd_m(2)  = ode_init_x[9 ] ;
      qd_m(3)  = ode_init_x[10] ;
      qd_m(4)  = ode_init_x[11] ;
      qd_m(5)  = ode_init_x[12] ;
      qd_m(6)  = ode_init_x[13] ;

      qdd_m(0) = m*( t_r(0) - d*ode_init_x[7 ] - k*ode_init_x[0 ] );
      qdd_m(1) = m*( t_r(1) - d*ode_init_x[8 ] - k*ode_init_x[1 ] );
      qdd_m(2) = m*( t_r(2) - d*ode_init_x[9 ] - k*ode_init_x[2 ] );
      qdd_m(3) = m*( t_r(3) - d*ode_init_x[10] - k*ode_init_x[3 ] );
      qdd_m(4) = m*( t_r(4) - d*ode_init_x[11] - k*ode_init_x[4 ] );
      qdd_m(5) = m*( t_r(5) - d*ode_init_x[12] - k*ode_init_x[5 ] );
      qdd_m(6) = m*( t_r(6) - d*ode_init_x[13] - k*ode_init_x[6 ] );
  }

};


class FirModel
{

  int num_Joints; // number of joints.
  int num_Fir   ; // number of FIR parameters.

  Eigen::MatrixXd q;
  Eigen::MatrixXd qd;
  Eigen::MatrixXd qdd;

  Eigen::MatrixXd q_m;
  Eigen::MatrixXd qd_m;
  Eigen::MatrixXd qdd_m;

  // Reference task model
  Eigen::MatrixXd ref_q_m;
  Eigen::MatrixXd ref_qd_m;
  Eigen::MatrixXd ref_qdd_m;

  Eigen::MatrixXd t_r;


  Eigen::MatrixXd Wk           ; // FIR weights
  Eigen::MatrixXd Uk           ; // Input
  Eigen::MatrixXd Uk_plus      ; // FIR inputs time series t_r temp to use for update
  Eigen::MatrixXd Dk           ; // Desired
  Eigen::MatrixXd Pk           ; // Covariance matrix

  double delT; // Time step

  double lm;
  
  int iter;

  // Task model
  double m ;
  double d ;
  double k ;

  state_type ode_init_x;

  oel::ls::RLSFilter rls_filter;

  void stackFirIn( Eigen::MatrixXd & in )
  {
    // TODO parameterize this
    // Moves up from bottom, rows are time series, columns are joints
    // First in First out top most location 0 th row is dumped
    Uk_plus.block<1,7>(8,0) = in;
    Uk_plus.block<8 - 1, 7>(0,0) = Uk.block<8 - 1, 7>(1,0);
    Uk = Uk_plus;
  }

public:
  FirModel()
  {
    delT = 0.001; /// 1000 Hz by default
    iter = 0;

    double a = 10;

    //          m    d    k
    init( 7, 8, a*a, 2*a, a*a );
  }
  ~FirModel()
  {
  }

  void init( int para_num_Joints, int para_num_Fir, double p_m, double p_d, double p_k )
  {
    m = p_m;
    d = p_d;
    k = p_k;

    num_Fir    = para_num_Fir;
    num_Joints = para_num_Joints;

    q     .resize( num_Joints, 1 ) ;
    qd    .resize( num_Joints, 1 ) ;
    qdd   .resize( num_Joints, 1 ) ;

    q_m   .resize( num_Joints, 1 ) ;
    qd_m  .resize( num_Joints, 1 ) ;
    qdd_m .resize( num_Joints, 1 ) ;

    ref_q_m   .resize( num_Joints, 1 ) ;
    ref_qd_m  .resize( num_Joints, 1 ) ;
    ref_qdd_m .resize( num_Joints, 1 ) ;

    t_r   .resize( num_Joints, 1 ) ;

    Wk    .resize( num_Fir, 1 ) ;
    Wk = Eigen::MatrixXd::Zero( num_Fir, 1 );

    Dk    .resize( num_Joints, 1 ) ;
    Dk = Eigen::MatrixXd::Zero( num_Joints, 1 );

    Pk    .resize( num_Fir, num_Fir       ) ;
    Pk = Eigen::MatrixXd::Identity( num_Fir, num_Fir )/0.0001;

    Uk.resize( num_Fir, num_Joints ) ;
    Uk = Eigen::MatrixXd::Zero( num_Fir, num_Joints );

    Uk_plus.resize( num_Fir, num_Joints ) ;
    Uk_plus = Eigen::MatrixXd::Zero( num_Fir, num_Joints );

    q   << 0, 0, 0, 0, 0, 0, 0 ;
    qd  << 0, 0, 0, 0, 0, 0, 0 ;
    qdd << 0, 0, 0, 0, 0, 0, 0 ;

    q_m   << 0, 0, 0, 0, 0, 0, 0 ;
    qd_m  << 0, 0, 0, 0, 0, 0, 0 ;
    qdd_m << 0, 0, 0, 0, 0, 0, 0 ;

    ref_q_m   << 0, 0, 0, 0, 0, 0, 0 ;
    ref_qd_m  << 0, 0, 0, 0, 0, 0, 0 ;
    ref_qdd_m << 0, 0, 0, 0, 0, 0, 0 ;

    t_r   << 0, 0, 0, 0, 0, 0, 0 ;

    lm = 1; // Forgetting factor

    // initial conditions
    ode_init_x[0 ] = 0.0;
    ode_init_x[1 ] = 0.0;
    ode_init_x[2 ] = 0.0;
    ode_init_x[3 ] = 0.0;
    ode_init_x[4 ] = 0.0;
    ode_init_x[5 ] = 0.0;
    ode_init_x[6 ] = 0.0;

    ode_init_x[7 ] = 0.0;
    ode_init_x[8 ] = 0.0;
    ode_init_x[9 ] = 0.0;
    ode_init_x[10] = 0.0;
    ode_init_x[11] = 0.0;
    ode_init_x[12] = 0.0;
    ode_init_x[13] = 0.0;

    ode_init_x[14] = 0.0;
    ode_init_x[15] = 0.0;
    ode_init_x[16] = 0.0;
    ode_init_x[17] = 0.0;
    ode_init_x[18] = 0.0;
    ode_init_x[19] = 0.0;
    ode_init_x[20] = 0.0;

    rls_filter.init( Wk, Uk, Dk, Pk, lm );

  }

  void updateDelT(double p_delT)
  {
    delT = p_delT;
  }

  void Update( Eigen::MatrixXd & qd_m  ,
               Eigen::MatrixXd & qd    ,
               Eigen::MatrixXd & q_m   ,
               Eigen::MatrixXd & q     ,
               Eigen::MatrixXd & qdd_m ,
               Eigen::MatrixXd & t_r    )
  {

    // Save input forces/torques
    stackFirIn( t_r );

    // Save iteration number
    iter = iter + 1;

    // Desired is the task reference model
    Dk = ref_q_m;

    if( iter > num_Fir )
    {
      rls_filter.Update( Wk, Uk, Dk, Pk );

      Wk = rls_filter.getEstimate();
      Pk = rls_filter.getCovariance();

      q_m   = Uk.transpose()*Wk  ;

      // Backward difference
      // TODO better way to do this?
      qd_m  = (q_m  - q_m )/delT ;
      qdd_m = (qd_m - qd_m)/delT ;
    }

      ode_init_x[14] = t_r(0);
      ode_init_x[15] = t_r(1);
      ode_init_x[16] = t_r(2);
      ode_init_x[17] = t_r(3);
      ode_init_x[18] = t_r(4);
      ode_init_x[19] = t_r(5);
      ode_init_x[20] = t_r(6);

      boost::numeric::odeint::integrate( task_model , ode_init_x , 0.0 , delT , delT );

      ref_q_m(0)   = ode_init_x[0 ] ;
      ref_q_m(1)   = ode_init_x[1 ] ;
      ref_q_m(2)   = ode_init_x[2 ] ;
      ref_q_m(3)   = ode_init_x[3 ] ;
      ref_q_m(4)   = ode_init_x[4 ] ;
      ref_q_m(5)   = ode_init_x[5 ] ;
      ref_q_m(6)   = ode_init_x[6 ] ;

      ref_qd_m(0)  = ode_init_x[7 ] ;
      ref_qd_m(1)  = ode_init_x[8 ] ;
      ref_qd_m(2)  = ode_init_x[9 ] ;
      ref_qd_m(3)  = ode_init_x[10] ;
      ref_qd_m(4)  = ode_init_x[11] ;
      ref_qd_m(5)  = ode_init_x[12] ;
      ref_qd_m(6)  = ode_init_x[13] ;

      ref_qdd_m(0) = m*( t_r(0) - d*ode_init_x[7 ] - k*ode_init_x[0 ] );
      ref_qdd_m(1) = m*( t_r(1) - d*ode_init_x[8 ] - k*ode_init_x[1 ] );
      ref_qdd_m(2) = m*( t_r(2) - d*ode_init_x[9 ] - k*ode_init_x[2 ] );
      ref_qdd_m(3) = m*( t_r(3) - d*ode_init_x[10] - k*ode_init_x[3 ] );
      ref_qdd_m(4) = m*( t_r(4) - d*ode_init_x[11] - k*ode_init_x[4 ] );
      ref_qdd_m(5) = m*( t_r(5) - d*ode_init_x[12] - k*ode_init_x[5 ] );
      ref_qdd_m(6) = m*( t_r(6) - d*ode_init_x[13] - k*ode_init_x[6 ] );
  }
};

}
}

#endif /* RLS_OUTER_LOOP_H_ */
