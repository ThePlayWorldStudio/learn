public class Vector{
	double[] coords = new double[3];
	Vector(int x, int y, int z){
		this.coords[0] = x;
		this.coords[1] = y;
		this.coords[2] = z;
	}



	public void PrintCoords(){
		for(int i = 0; i<3; i++){
			System.out.print(coords[i]);
		}
	}
	public double[] coords(){
		return coords;
	}

	public void plus(Vector vec2){
		for(int i = 0; i<3; i++){
			this.coords[i] += vec2.coords[i];
		}
	}

	public void minus(Vector vec2){
		for(int i = 0; i<3; i++){
			this.coords[i] -= vec2.coords[i];
		}
	}

	public double scalmultiply(Vector vec2){
		double answ = 0;
		for(int i = 0; i<3; i++){
			answ += this.coords[i] * vec2.coords[i];
		}
		return answ;
	}

	public double scalmultiply(double koef){
		double answ = 0;
		for(int i = 0; i<3; i++){
			answ += this.coords[i] * koef;
		}
		return answ;
	}

	public double divide(Vector vec2){
		double answ = 0;
		for(int i = 0; i<3; i++){
			answ += this.coords[i] * vec2.coords[i];
		}
		return answ;
	}	

	private double length(){
		double answ = 0;
		for(int i = 0; i<3; i++){
			answ += this.coords[i]*this.coords[i];
		}
		return Math.sqrt(answ);
	}

	public double cosinus(Vector vec2){
		return this.scalmultiply(vec2)/(this.length()*vec2.length());
	}

	public boolean bigger(Vector vec2){
		if(this.length()>vec2.length()){
			return true;
		} else {
			return false;
		}
	
	}

	public boolean equal(Vector vec2){
		if(this.length()==vec2.length()){
			return true;
		} else {
			return false;
		}
	}
}
