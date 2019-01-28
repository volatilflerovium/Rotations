/*********************************************************************
* Vector and rotation template classes                               *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-11-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H
using namespace std;

//README: for value of pi use M_PI which is part of cmath
//const double pi=3.1415926535897; 

//###################################################################
//###################################################################
	
template<int D>
class Vect
{
	private:
		unsigned short dimension;		
		double V[D];

	public:
		Vect();
		Vect(const Vect<D>& v);
		Vect(double* coordinates, int size);
		Vect(std::initializer_list<double> l);
		int get_dimension() const;
		virtual Vect<D>& operator=(const Vect<D>& v);
		bool operator!=(const Vect<D>& v);
		Vect<D>& operator+=(const Vect<D>& w);
		Vect<D> operator+(const Vect<D>& W);
		Vect<D> operator-(const Vect<D>& W);
		Vect<D>& operator*=(double f);
		Vect<D>& operator-=(const Vect<D>& w);
		double get_coordinate(int n) const;
		double norm() const;
		Vect<D>& canonical_reflexion(int p);
		Vect<D>& normalize();
};

//===================================================================

template<int D>
int Vect<D>::get_dimension() const{
	return this->dimension;
}

//===================================================================

template<int D>
Vect<D>::Vect(){
	this->dimension=D;
	for(int i=0; i<D; i++){
		this->V[i]=0;
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(std::initializer_list<double> l){
	this->dimension=D;
	int i=0;
	for(double x : l){
		this->V[i++]=x;
		if(i==D){
			break;
		}
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(double* coordinates, int size){
	this->dimension=D;
	for(int i=0; i<D; i++){
		if(i<size){
			this->V[i]=coordinates[i];
		}
		else{
			this->V[i]=0;
		}
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(const Vect<D>& v){
	this->dimension=v.get_dimension();
	for(int i=0; i<this->dimension; i++){
		this->V[i]=v.get_coordinate(i);
	}
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator=(const Vect<D>& v){
	if(this!=&v){
		if(this->dimension==v.get_dimension()){
			for(int i=0; i<this->dimension; i++){
				this->V[i]=v.get_coordinate(i);		
			}
		}
		else{
			cout<<"catch exception!!!\n";
		}
	}
	return *this;
}

//===================================================================

template<int D>
bool Vect<D>::operator!=(const Vect<D>& v){
	bool a=(this==&v);
	if(!a){
		for(int i=0; i<this->dimension; i++){
			if(this->V[i]!=v.get_coordinate(i)){
				a=true;
				break;	
			}
		}
	}
	return a;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator+=(const Vect<D>& v){
	for(int i=0; i<this->dimension; i++){
		this->V[i]+=v.get_coordinate(i);		
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D> Vect<D>::operator+(const Vect<D>& W){ 
	double v[D];
	for(int i=0; i<D; i++){
		v[i]=this->get_coordinate(i)+W.get_coordinate(i);		
	}
	Vect<D> V(v, D);
	return V;
}

//===================================================================

template<int D>
Vect<D> Vect<D>::operator-(const Vect<D>& W){	
	double v[D];
	for(int i=0; i<D; i++){
		v[i]=this->get_coordinate(i)-W.get_coordinate(i);		
	}
	Vect<D> V(v, D);
	return V;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator*=(double f){
	for(int i=0; i<D; i++){
		this->V[i]*=f;		
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator-=(const Vect<D>& v){
	for(int i=0; i<this->dimension; i++){
		this->V[i]-=v.get_coordinate(i);		
	}
	return *this;
}

//===================================================================

template<int D>
double Vect<D>::norm() const{
	double sum=0;
	for(int i=0; i<this->dimension; i++){
		sum+=this->V[i]*this->V[i];
	}
	return sqrt(sum);
}

//===================================================================

template<int D>
double Vect<D>::get_coordinate(int n) const{
	if(n<this->dimension){
		return this->V[n];
	}
	else{
		cout<<"Throw an exception!\n";	
	}
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::normalize(){
	(*this)*=1/norm();
	return *this;
}

//===================================================================

/*
This is a reflexion with respect to the hyperplane orthogonal to the p-th
element of the canonical base.
*/

template<int D>
Vect<D>& Vect<D>::canonical_reflexion(int p){
	if(p<this->dimension){
		this->V[p]*=-1;
	}
	return *this;
}


//===================================================================
//###################################################################
//===================================================================

template<int D>
Vect<D> operator*(double f, const Vect<D>& v){
	double vw[v.get_dimension()];
	for(int i=0; i<v.get_dimension(); i++){
		vw[i]=f*(v.get_coordinate(i));
	}
	Vect<D> w(vw, v.get_dimension());	
	return w;
}

//===================================================================

template<int D>
Vect<D> operator*(const Vect<D>& v, double f){
	return f*v;
} 

//===================================================================

template<int D>
Vect<D> operator/(const Vect<D>& v, double f){
	return (1.0/f)*v;
}
 
//===================================================================


template<int D>
Vect<D> operator+(const Vect<D>& u, const Vect<D>& v){
	if(u.get_dimension()==v.get_dimension()){
		int n=u.get_dimension();
		double vw[n];
		for(int i=0; i<n; i++){
			vw[i]=u.get_coordinate(i)+v.get_coordinate(i);
		}
		Vect<D> w(vw, n);
		return w;
	}
}

//===================================================================

template<int D>
Vect<D> operator-(const Vect<D>& u, const Vect<D>& v){
	if(u.get_dimension()==v.get_dimension()){
		return u+(-1)*v;
	}
}

//===================================================================

template<int D>
ostream& operator<<(ostream& out, const Vect<D>& v){
	int d=v.get_dimension();
	out<<'(';
	for(int i=0; i<d; i++){
		out<<v.get_coordinate(i);
		if(i<d-1){
			out<<',';
		}
	}
	out<<')';
	return out;
}

//===================================================================

template<int D>
double dot_prod(const Vect<D>& v, const Vect<D>& w){
	double dprod=0;
	for(int i=0; i<D; i++){
		dprod+=v.get_coordinate(i)*w.get_coordinate(i);
	}
	return dprod;
}

//===================================================================

template<int D>
double ang_cos(const Vect<D>& v, const Vect<D>& w){
	return dot_prod(v, w)/(v.norm()*w.norm());
}

//===================================================================

template<int D>
double distance(const Vect<D>& v, const Vect<D>& w){
	double sum=0;
	for(int i=0; i<v.get_dimension; i++){
		sum+=pow(v.get_coordinate(i)-w.get_coordinate(i), 2);
	}
	return sqrt(sum);
}


//===================================================================
//################################################################### 
//################################################################### 
//################################################################### 
//################################################################### 
//################################################################### 
//###################################################################

template<int D>
class Rotation
{
	private:
		double rad;
		Vect<D> P1;
		Vect<D> P2;
		Vect<D> Q;
		Vect<D> Offset;
		void setup(Vect<D> rotation_axe);
		void set_angle(double angle);

	public:
		Rotation(Vect<D> V, double angle);
		Rotation(Vect<D> V, Vect<D> W, double angle);
		Rotation(std::initializer_list<double> l, double angle);
		Rotation(std::initializer_list<double> lp, std::initializer_list<double> lq, double angle);
		Vect<D> operator()(const Vect<D>& v);
		Vect<D> operator()(double ang, const Vect<D>& V);
};


//===================================================================

template<int D>
Rotation<D>::Rotation(Vect<D> rotation_axe, double angle){
	Vect<D> O;
	Offset=O;
	set_angle(angle);
	setup(rotation_axe);
}

//===================================================================

template<int D>
Rotation<D>::Rotation(std::initializer_list<double> l, double angle){
	Vect<D> O;
	Offset=O;
	set_angle(angle);
	Vect<D> V(l);
	setup(V);
}

//===================================================================


template<int D>
Rotation<D>::Rotation(std::initializer_list<double> lp, std::initializer_list<double> lq, double angle){
	set_angle(angle);
	Vect<D> V(lp);
	Vect<D> U(lq);
	Offset=U;
	setup(V-U);
}

//===================================================================

template<int D>
Rotation<D>::Rotation(Vect<D> V, Vect<D> W, double angle){
	Offset=W;
	set_angle(angle);
	setup(V-W);
}

//===================================================================

template<int D>
void Rotation<D>::set_angle(double angle){
	if(fabs(angle)>=360.0){
		angle=(fabs(angle)/angle)*(fabs(angle)-360.0);
	}

	rad=((angle/2)*M_PI)/180;
}

//===================================================================

template<int D>
void Rotation<D>::setup(Vect<D> rotation_axe){

	/*
	First we get a canonical solution to the equation axe dot v=0.
	This is everything zero except 2 for example
	axe =(a,b,c,d);
	v=(0,c,-b,0); where b and c are, at least one, not zero
	*/
	double a[D];
	a[0]=0;
	a[1]=0;
	double b[D];
	b[0]=1;
	b[1]=1;
	double s[D];
	s[0]=1;
	s[1]=1;
	int P[2]={0,1};
	// we get two non zero values
	if(D>2){
		for(int i=2; i<D; i++){
			a[i]=0;
			b[i]=1;
			s[i]=1;
			if(fabs(rotation_axe.get_coordinate(P[0]))+fabs(rotation_axe.get_coordinate(P[1]))==0){
				if(rotation_axe.get_coordinate(i)>0.0){
					P[0]=i-1;
					P[1]=i;
				}
			}
		}
		
		//cout<<P[0]<<" "<<P[1]<<endl;
		
		a[P[0]]=rotation_axe.get_coordinate(P[1]);
		a[P[1]]=-1.0*rotation_axe.get_coordinate(P[0]);
		Vect<D> p(a, D);
		
		b[P[0]]=0;
		b[P[1]]=0;
		Vect<D> B(b, D);
	  
	   /*
		 Now, we use p to construct an orthogonal vector W 
		 WE CAN USE the cross product!! 
		 NOOO, of course NOT!!! 
		 we need something easy and fast
		*/
		double r=0;
		r=rotation_axe.get_coordinate(P[0])*p.get_coordinate(P[1]);
		r-=rotation_axe.get_coordinate(P[1])*p.get_coordinate(P[0]);
		s[P[0]]=(-1.0*dot_prod(B, rotation_axe)*p.get_coordinate(P[1]))/r;
		s[P[1]]=(dot_prod(B, rotation_axe)*p.get_coordinate(P[0]))/r;
		Vect<D> W(s, D);
		P1=p.normalize();
		P2=W.normalize();
		Q=sin(rad)*P2+cos(rad)*P1;
	}
	else{
		Vect<D> v({1, 0});
		P1=v;
		Vect<D> w({0, 1});
		P2=w;
		Q=sin(rad)*P2+cos(rad)*P1;
	}
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::operator()(const Vect<D>& V){
	double t=2*dot_prod(V-Offset, Q);
	return V-t*Q+(t*2*cos(rad)-2*dot_prod(V-Offset, P1))*P1;
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::operator()(double ang, const Vect<D>& V){
	static double local_ang=0;
	if(ang!=local_ang){
		local_ang=ang;
		Q=sin(rad)*P2+cos(rad)*P1;
	}
	double t=2*dot_prod(V-Offset, Q);
	return V-t*Q+(t*2*cos(rad)-2*dot_prod(V-Offset, P1))*P1;
}



//===================================================================




#endif


