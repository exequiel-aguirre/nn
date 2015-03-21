#ifndef MatrixH
#define MatrixH

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
			os<< m.rawMatrix[i]<<" ";
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

	Matrix getInverse(){
		float e[4][8]={0};

		//build the extended matrix e=[a|I]
		for(int i=0;i<4;i++){
			for(int j=0;j<8;j++){
				if(j<4) e[i][j]=rawMatrix[4*i + j];
				if(i==(j-4)) e[i][j]=1.0;
			}
		}

		//reduce to diagonal
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(i!=j && e[i][i]!=0){
					float d=e[j][i]/e[i][i];
					for(int k=0;k<8;k++){
						e[j][k]-=e[i][k]*d;
					}
				}
			}
		}

		//reduce to unit
		for(int i=0;i<4;i++){
			float d=e[i][i];
			if(d==0) continue;
			for(int j=0;j<8;j++){
				e[i][j]=e[i][j]/d;
			}
		}

		//build the inverse Matrix
		Matrix inverse;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				inverse.rawMatrix[4*i + j]=e[i][j+4];
			}
		}

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
	
};

#endif