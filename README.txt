							*****************************

							** Description of the exam **

							*****************************
MOTOR (87:1 Metal Gearmotor 3-12V with a Torque of 1.5KGF/CM and a Velocity of 100RPM): 

This is the information about the components and parts for the motors of the wheels of our robot we use a yelow gearmotor with a gearbox 87:1 and torque of 1.5KGF/CM and a speed of 100 RPM.

For the Max velocity that was 100 rpm that we had to converted to rad/seconds so we know that 1 revolution is equal to 2pi/rad, so we multiply the 100 revolution for 2pi and we obtain 100*2pi= 200pi, then we divide between 60 that is equal to 200pi/60=10.4719755.


For the Max torque that we have from the information of the page 1.5KGF/CM we know that 1kgf/cm is equal to 0.1N*m so we can apply a rule of three here, we multiply 1.5 for 0.1 and this is equal to 1.5*0.1= .15 is our result.


For the resolution of the distance sensor that we implemented, in the datasheet we found that it has an operative range from 2cm to 500cm, and we have a resolution of .3cm, so we apply the formula that is (maxdistance-mindistance)/resolution, so it was (2-500)/.3= 1660 and this is the value that we are going to use when we have the maximun distance, for the minimun distance we use 0.


Lookup table of the distance sensor

0	0	0
0.02	0	0
5	1660	0


ENCODER:

The resolution was calculated using the formula found in this link: https://www.cui.com/blog/what-is-encoder-ppr-cpr-and-lpr
I mean (2 * PI)/(20) since the grooves are 20 and the increasing part of the pulse was used, that is 1. Therefore the resolution can be said to be 0.3141 rad, that is the minimun change.



The following are links in which you can find extra information about the encoders and the dc motors that we implemented.
Encoder link: http://www.electronicathido.com/index.php?id_product=1057&controller=product&search_query=encoder&results=4
http://www.electronica60norte.com/producto/disco-encoder-20-perforaciones
Dc motor link: https://articulo.mercadolibre.com.mx/MLM-561883837-motor-dc-con-caja-reductora-arduino-robotica-actuador-pic-_JM?quantity=1

JUSTIFICATION:

Given that our robot has a max velocity of 10.479 rad/s and the choosen velocity both for manual and autonomous, in other 
wordsa 0.15 for the manual, 0.12 for the autonomous velocity.If we reach the max velocity, the robot will to work incorrectly 

INSTRUCTIONS:

The robot stars in the point 0,0.05,0 wiht respect the floor.at the start of the world the robot go forward until detect the 
object that is nearly to the right and do one spin to the left, once it has complete one spin and has free way, it will go forward
to the next obstacle that is nearly to the left and it will do one spin to the right. it will avoid obtacles wihtout end.
it could be one case where the robot get stock in a corner, becausen the robot does have one compare distance less or greater.
the robot can be settled in manual status with the "W" key int.
