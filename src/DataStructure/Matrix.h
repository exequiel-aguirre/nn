#ifndef MatrixH
#define MatrixH
#include <vector>
class Matrix{
  public:
   float rawMatrix[16];

	Matrix(float a,float b,float c,float d){
		loadDiagonal(a,b,c,d);
	}	
	Matrix(float a):Matrix(a,a,a,a){}
	Matrix():Matrix(0.0){}

	Matrix(float rawMatrix[16]){
		for(int i=0;i<16;i++) this->rawMatrix[i]=rawMatrix[i];
	}



	float* getRawMatrix(){
		return rawMatrix;
	}

	float operator [](int i) const{//getter
		return rawMatrix[i];
	}

	Matrix operator*(const Matrix& b){
		Matrix a=(*this);
		a*=b;
		return a;
	}
	Matrix& operator*=(const Matrix& bm){
		Matrix am=(*this);
		const float* a=am.rawMatrix;
		const float* b=bm.rawMatrix;
		//cij=aik bkj k=1..4;
		rawMatrix[0]=(a[0] * b[0]) + (a[1] * b[4]) + (a[2] * b[8]) +(a[3] * b[12]);
		rawMatrix[1]=(a[0] * b[1]) + (a[1] * b[5]) + (a[2] * b[9]) +(a[3] * b[13]);
		rawMatrix[2]=(a[0] * b[2]) + (a[1] * b[6]) + (a[2] * b[10]) +(a[3] * b[14]);
		rawMatrix[3]=(a[0] * b[3]) + (a[1] * b[7]) + (a[2] * b[11]) +(a[3] * b[15]);

		rawMatrix[4]=(a[4] * b[0]) + (a[5] * b[4]) + (a[6] * b[8]) +(a[7] * b[12]);
		rawMatrix[5]=(a[4] * b[1]) + (a[5] * b[5]) + (a[6] * b[9]) +(a[7] * b[13]);
		rawMatrix[6]=(a[4] * b[2]) + (a[5] * b[6]) + (a[6] * b[10]) +(a[7] * b[14]);
		rawMatrix[7]=(a[4] * b[3]) + (a[5] * b[7]) + (a[6] * b[11]) +(a[7] * b[15]);

		rawMatrix[8]=(a[8] * b[0]) + (a[9] * b[4]) + (a[10] * b[8]) +(a[11] * b[12]);
		rawMatrix[9]=(a[8] * b[1]) + (a[9] * b[5]) + (a[10] * b[9]) +(a[11] * b[13]);
		rawMatrix[10]=(a[8] * b[2]) + (a[9] * b[6]) + (a[10] * b[10]) +(a[11] * b[14]);
		rawMatrix[11]=(a[8] * b[3]) + (a[9] * b[7]) + (a[10] * b[11]) +(a[11] * b[15]);

		rawMatrix[12]=(a[12] * b[0]) + (a[13] * b[4]) + (a[14] * b[8]) +(a[15] * b[12]);
		rawMatrix[13]=(a[12] * b[1]) + (a[13] * b[5]) + (a[14] * b[9]) +(a[15] * b[13]);
		rawMatrix[14]=(a[12] * b[2]) + (a[13] * b[6]) + (a[14] * b[10]) +(a[15] * b[14]);
		rawMatrix[15]=(a[12] * b[3]) + (a[13] * b[7]) + (a[14] * b[11]) +(a[15] * b[15]);

		return (*this);
	}

	Matrix& operator*=(const float a){
		for(int i=0;i<16;i++){
			rawMatrix[i]*=a;
		}
		return (*this);
	}

	Matrix operator-(const Matrix& b){
		Matrix a=(*this);
		for(int i=0;i<16;i++){
			a.rawMatrix[i]-=b.rawMatrix[i];
		}
		return a;
	}
	friend std::ostream& operator<<(std::ostream& os , const Matrix m){
		for(int i=0;i<16;i++){
			if((i%4)==0) os<< std::endl;
			os<< std::fixed<<m.rawMatrix[i]<<((m.rawMatrix[i]<0.0)?" ":"  ");
		}
		return os<<std::endl;
	}

	void loadIdentity(){		
		loadDiagonal(1.0);
	}
	void loadDiagonal(float a){
		loadDiagonal(a,a,a,a);
	}
	void loadDiagonal(float a,float b,float c,float d){
		loadZero();
		rawMatrix[0]=a; //a 0 0 0
		rawMatrix[5]=b; //0 b 0 0
		rawMatrix[10]=c;//0 0 c 0
		rawMatrix[15]=d;//0 0 0 d	
	}

	void loadZero(){
		for(int i=0;i<16;i++){
			rawMatrix[i]=0;
		}
	}

	void translate(float x,float y,float z){
		Matrix t=getTranlationMatrix(x,y,z);
		(*this)*=t;
	}
	Matrix getTranlationMatrix(float x,float y,float z){
		float t[16]={
			1 , 0 , 0 , x ,
			0 , 1 , 0 , y ,
			0 , 0 , 1 , z ,
			0 , 0 , 0 , 1 };

		return Matrix(t);
	}

	void rotate(float angle,float x,float y,float z){
		if(angle==0) return;
		Matrix r=getRotationMatrix(angle,x,y,z);
		(*this)*=r;
	}
	Matrix getRotationMatrix(float angle,float x,float y,float z){
		angle=angle*M_PI/180.0f;
		float c=cos(angle);
		float s=sin(angle);
		float r[16]={
			c + x*x*(1-c)     , x*y*(1-c) - (z*s) , x*z*(1-c) + y*s , 0 ,
			y*x * (1-c) + z*s , c + y*y*(1-c)     , y*z*(1-c) -x*s  , 0 ,
			z*x*(1-c) - y*s   , z*y*(1-c) + x*s   , c + z*z*(1-c)   , 0 ,
			0                 , 0                 , 0               , 1 };

		return Matrix(r);
	}

	void scale(float a,float b,float c){
		Matrix s=Matrix(a,b,c,1.0);
		(*this)*=s;
	}

	void perspective(float angle,float aspectRatio,float near,float far){
		Matrix p=getPerspectiveMatrix(angle,aspectRatio,near,far);
		(*this)*=p;
	}

	Matrix getPerspectiveMatrix(float angle,float aspectRatio,float near,float far){
		// gluPerspective(angle * 2.0f, x/y, near, far);
		float fH = tan( angle ) * near;
		float fW = fH * aspectRatio;

		float w=near/fW;
		float h=near/fH;
		float q=-(far+near)/(far-near);
		float qn=-2*(far*near)/(far-near);

		float p[16]={
			w , 0 , 0  , 0  ,
			0 , h , 0  , 0  ,
			0 , 0 , q  , -1 ,
			0 , 0 , qn , 0  };

		return Matrix(p);
	}

	//TODO:implement this
	/*This will work fine until we use the scale (for the reflection,for example)
	*/
	Matrix getNormalMatrix(){
		//transpose(inverse(gl_ModelViewMatrix))
		//return (*this).getInverse().transpose();
		return (*this);
	}

	Matrix getInverse()
	{
	float* m=this->rawMatrix;
    float inv[16];

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0){
        std::cout << "not invertible!!!"<<(*this);exit(4);
    }

    det = 1.0 / det;

    Matrix inverse;
    for (int i = 0; i < 16; i++)
        inverse.rawMatrix[i] = inv[i] * det;

    return inverse;
}

	Matrix& transpose(){
		Matrix a=(*this);
		for (int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				rawMatrix[4*i +j]=a[4*j +i];
			}
		}
		return (*this);
	}
	
	Matrix getRotationMatrix(){
		Matrix r=(*this);
		r.rawMatrix[3]=0;
		r.rawMatrix[7]=0;
		r.rawMatrix[11]=0;
		r.rawMatrix[15]=1;
		return r;
	}
	Matrix getTranslationMatrix(){
		Matrix t=this->getTranlationMatrix(rawMatrix[3],rawMatrix[7],rawMatrix[11]);
		return t;
	}

	void rotate(float heading, float attitude, float bank){
		heading*=M_PI/180.0f;
		attitude*=M_PI/180.0f;
		bank*=M_PI/180.0f;
		float c1=cos(heading/2.0);
		float c2=cos(attitude/2.0);
		float c3=cos(bank/2.0);

		float s1=sin(heading/2.0);
		float s2=sin(attitude/2.0);
		float s3=sin(bank/2.0);

		float x=(s1*s2*c3) + (c1*c2*s3);
		float y=(s1*c2*c3) + (c1*s2*s3);
		float z=(c1*s2*c3) - (s1*c2*s3);
		float w=c1*c2*c3-s1*s2*s3;
		float norm= sqrt(x*x + y*y + z*z);
		if(norm<0.001){
			x=1;
			y=z=0;
		}
		else{
			x/=norm;
			y/=norm;
			z/=norm;
		}
		float angle=2.0*acosf(w) *(180.0f/M_PI);//vs 2*acos(c1*c2*c3-s1*s2*s3) *180.0f/M_PI;

		rotate(angle,x,y,z);
	}

    std::vector<float> getEulerAngles(){
        float heading,attitude,bank;
        float m10=rawMatrix[4*1 + 0];
        const float C=0.998;
        if(m10<-C || C<m10)
        {
            heading=atan2(rawMatrix[4*0 + 2],rawMatrix[4*2 + 2]);
            attitude=(m10<-C)?-M_PI/2.0f:M_PI/2.0f;
            bank=0;
        }
        else
        {
            heading=atan2(-rawMatrix[4*2 + 0],rawMatrix[4*0 + 0]);
            attitude=asin(rawMatrix[4*1 + 0]);
            bank=atan2(-rawMatrix[4*1 + 2],rawMatrix[4*1 + 1]);
        }


        float radToGrad=(180.0f/M_PI);
        std::vector<float> xyz=std::vector<float>({heading*radToGrad,attitude*radToGrad,bank*radToGrad});
        return xyz;
    }
};

#endif