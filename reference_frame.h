#ifndef REF_FRAME_H
#define REF_FRAME_H

class ReferenceFrame
{
   private:
      double origen_x;
      double origen_y;
      double ration;
      const double px_per_cm;
      ReferenceFrame();				//forbids ClassA A()
      ReferenceFrame(const ReferenceFrame&);			//forbids ClassA A=B; another version of A(B)
      ReferenceFrame& operator=(const ReferenceFrame& RF); // forbids ClassA A; A=B

   public:
   
   	//ReferenceFrame() = delete;
      ReferenceFrame(double x, double y, double size=0.0);// size in cm
      double operator()(double z, char t);
      const double& rt() const;
};

//-------------------------------------------------------------------

inline const double& ReferenceFrame::rt() const{
   return ration;
}

//-------------------------------------------------------------------

//-------------------------------------------------------------------

#endif