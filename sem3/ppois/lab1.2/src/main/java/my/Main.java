package my;

import my.vector.Vector;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	
	private int menuVector(){
		ArrayList<Vector> vectors = new ArrayList<>();
		Scanner in = new Scanner(System.in);

		System.out.println("Choose operation with vectors:");
		System.out.println("1. add new vector");
		System.out.println("2. get coords");
		System.out.println("3. plus");
		System.out.println("4. minus");
		System.out.println("5. multply");
		System.out.println("6. divide");
		System.out.println("7. assertion");
		System.out.println("8. exit");

		boolean isWork = true;
		int choose;

		while(isWork){
			choose = in.nextInt();
			switch(choose){
				case 1:
					System.out.println("Enter coords (x y z):");
					int x = in.nextInt();
					int y = in.nextInt();
					int z = in.nextInt();
					Vector temp = new Vector(x, y, z);
					vectors.add(temp);
					System.out.printf("Was added vector with index %d", vectors.size());
				case 2:
					if(vectros.size<1){
						System.out.println("No vectors");
					} else {
						System.out.println("Which vector?");
						int n = in.nextInt() - 1;
						vectors.get(n).PrintCoords();
					}
				case 3:
					if(vectors.size() < 2){
						System.out.println("not many vectors");
					} else {
						System.out.println("choose 1 vector: ");
						int first = in.nextInt() - 1;
						int second = in.nextInt() - 1;

						vectors.get(first).plus(vectors.get(second));
						System.out.println("Success");
					}
		return 0;
	}

	private int menuTuring(){
		System.out.println("");
		return 0;
	}

	public static void main(){
		Scanner in = new Scanner(System.in);
		boolean isWorks = true;
		
		while(isWorks){
			System.out.println("Which option choose?\n   1. Turing\n   2. Vector");
			int choose = in.nextInt();
			if(choose != 1 || choose != 2){
				System.out.println("Incorrect input!");
			} else {
				isWork = false;
			}
		}	

		switch(choose){
			case 1:
				menuTuring();
				
			case 2:
				menuVector();
		}
	}
}


