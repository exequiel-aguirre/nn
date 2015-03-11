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

	virtual ~Matrix(){}

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
	Matrix& operator*=(const Matrix& b){
		Matrix a=(*this);
		//cij=aik bkj k=1..4;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				float c_ij=0;
				for(int k=0;k<4;k++) c_ij += a.rawMatrix[4*i + k] * b.rawMatrix[4*k + j];
				rawMatrix[4*i + j]=c_ij;
			}
		}		

		return (*this);
	}

	Matrix& operator*=(const float a){
		for(int i=0;i<16;i++){
			rawMatrix[i]*=a;
		}
		return (*this);
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
		float t[16]={0};		
		t[0]=1;
		t[3]+=x; //1 0 0 x
		t[5]=1;
		t[7]+=y; //0 1 0 y		
		t[10]=1;
		t[11]+=z;//0 0 1 z
		t[15]=1.0;//0 0 0 1	

		return Matrix(t);
	}

	void rotate(float angle,float x,float y,float z){
		if(angle==0) return;
		Matrix r=getRotationMatrix(angle,x,y,z);
		(*this)*=r;
	}
	Matrix getRotationMatrix(float angle,float x,float y,float z){
		float r[16];		
		angle=angle*M_PI/180.0f;
		float c=cos(angle);
		float s=sin(angle);
		r[0]=c + x*x*(1-c);
		r[1]=x*y*(1-c) - (z*s);
		r[2]=x*z*(1-c) + y*s;
		r[3]=0;

		r[4]=y*x * (1-c) + z*s;
		r[5]=c + y*y*(1-c);
		r[6]=y*z*(1-c) -x*s;
		r[7]=0;

		r[8]=z*x*(1-c) - y*s;
		r[9]=z*y*(1-c) + x*s;
		r[10]=c + z*z*(1-c);
		r[11]=0;

		r[12]=0;
		r[13]=0;
		r[14]=0;
		r[15]=1;

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
		float p[16]={0};
		// gluPerspective(angle * 2.0f, x/y, near, far);
		float fH = tan( angle ) * near;
		float fW = fH * aspectRatio;

		float w=near/fW;
		float h=near/fH;
		float q=-(far+near)/(far-near);
		float qn=-2*(far*near)/(far-near);

		p[0]=w;

		p[5]=h;

		p[10]=q;
		p[11]=-1;

		p[14]=qn;

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