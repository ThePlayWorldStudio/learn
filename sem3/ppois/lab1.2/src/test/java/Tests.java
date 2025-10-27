import org.junit.Test;
import org.junit.Before;
import org.junit.After;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertArrayEquals;

import my.vector.Vector;

public class Tests {
	
	@SuppressWarnings({"unchecked", "rawtypes"})
	@Test
	public void testCoords() {
		Vector vec = new Vector(1, 2, 3);
		double[] excepted = {1, 2, 3};
		assertArrayEquals(excepted, vec.Coords(), 0.0);
	}

	@Test 
	public void testPlus() {
		Vector vec1 = new Vector(1, 2, 3);
		Vector vec2 = new Vector(3, 2, 1);
		double[] excepted = {4, 4, 4};

		vec1.plus(vec2);

		assertArrayEquals(excepted, vec1.Coords(), 0.0);
	}

	@Test 
	public void testMinus() {
		Vector vec1 = new Vector(1, 2, 3);
		Vector vec2 = new Vector(3, 2, 1);
		double[] excepted = {-2, 0, 2};

		vec1.minus(vec2);

		assertArrayEquals(excepted, vec1.Coords(), 0.0);
	}

	@Test 
	public void testMultiplyVector() {
		Vector vec1 = new Vector(1, 2, 3);
		Vector vec2 = new Vector(3, 2, 1);
		double excepted = 10;

		assertEquals(excepted, vec1.scalMultiply(vec2), 0.0);
	}

	@Test 
	public void testMultiplyKoeff() {
		Vector vec1 = new Vector(1, 2, 3);
		double excepted = 12;

		assertEquals(excepted, vec1.scalMultiply(2), 0.0);
	}

	@Test 
	public void testDivideKoeff() {
		Vector vec1 = new Vector(2, 4, 6);
		double excepted = 6;

		assertEquals(excepted, vec1.divide(2), 0.0);
	}

	@Test 
	public void testDivideVector() {
		Vector vec1 = new Vector(4, 6, 8);
		Vector vec2 = new Vector(2, 2, 2);
		double excepted = 9;

		assertEquals(excepted, vec1.divide(vec2), 0.0);
	}

}	
