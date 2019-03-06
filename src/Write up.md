#Write up

This is the write up for PID Controller project.


1. Implementation.

The PID procedure was coded in the PID.cpp and PID.h files. The main process of PID control was defined in the function PID::Steer().

2. Describe the effect each of the P, I, D components had in your implementation.

The P components prevent the car drive off the center of the lane and I and D component prevent over steering.

3. Describe how the final hyperparameters were chosen.

By twiddle. The twiddle method is defined in the UpdateError function in PID.cpp. I thought it would be nice to update the coefficient while update the error.

However, I also manually choose the initial hyperparameters. If not, the car might drive off the road from the very beginning.

4.The vehicle must successfully drive a lap around the track.

Yes, it did. I record part of it in the small mov file naming PID-Controller-video.mov.