#include "PID.h"
#include <cmath>


using namespace std;

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  PID::Kp = Kp_;
  PID::Ki = Ki_;
  PID::Kd = Kd_;

  PID::p_error = 0.1 * Kp_;
  PID::i_error = 0.1 * Ki_;
  PID::d_error = 0.1 * Kd_;

  PID::Kp += PID::p_error;
  PID::Ki += PID::i_error;
  PID::Kd += PID::d_error;

  PID::best_err = 999999999999999.0;
  PID::count = 1;
  PID::total_cte = 0;

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */

  PID::prev_cte = cte;
  PID::total_cte += cte;
  if(PID::count%100 == 0)
  {
    PID::total_cte = 0;
  }
  double sum_dp = PID::p_error + PID::i_error + PID::d_error;
  if(sum_dp > 0.00001)
  {
    //PID::count++;
    
    if(cte < best_err)
    {
      best_err = cte;
      PID::p_error *= 1.1;
      PID::i_error *= 1.1;
      PID::d_error *= 1.1;
      PID::Kp += PID::p_error;
      PID::Ki += PID::i_error;
      PID::Kd += PID::d_error;
      return;
    }
    else
    {
      if(PID::count%2 == 0)
      {
        PID::Kp -= 2*PID::p_error;
        PID::Ki -= 2*PID::i_error;
        PID::Kd -= 2*PID::d_error;
        PID::count++;
        return;
      }
      else if(PID::count%2 == 1)
      {
        PID::Kp += PID::p_error;
        PID::Ki += PID::i_error;
        PID::Kd += PID::d_error;
        PID::p_error *= 0.9;
        PID::i_error *= 0.9;
        PID::d_error *= 0.9;
        PID::Kp += PID::p_error;
        PID::Ki += PID::i_error;
        PID::Kd += PID::d_error;
        PID::count++;
        return;
      }
    }
  }
}

//double PID::TotalError(cte) {
  /**
   * TODO: Calculate and return the total error
   */
//  double total_error = p_error + i_error + d_error;

//  return total_error;  // TODO: Add your total error calc here!
//}


double PID::Steer(double cte){
  double delta_cte = cte - PID::prev_cte;
  double x = -PID::Kp * cte - PID::Kd * delta_cte - PID::Ki * PID::total_cte;
  double steer_value;
  //steer_value = 2.0/(1+exp(-x))-1;
  steer_value = x/(1+fabs(x));
  
  return steer_value;



}