
#include "reference_frame.h"
//#include "helper.h"


//-------------------------------------------------------------------

//const ReferenceFrame::ration=1.0;

//-------------------------------------------------------------------

ReferenceFrame::ReferenceFrame(double x, double y, double size) // size is metres to scale down to 1 cm
       :origen_x(x), origen_y(y), ration(1), px_per_cm(37.795238)
{
   //1cm=37.7952 px (depending of the resolution)
  // double cms=w_height/37.7952;
   //cms=ration*size
   if(size>0)
   {
      ration=px_per_cm/(1.0*size);
   }
}

//-------------------------------------------------------------------

double ReferenceFrame::operator()(double z, char t){
   if(t=='x'){
      return origen_x+z;
   }
   else{
      return origen_y-1.0*z;
   }
}


//-------------------------------------------------------------------
