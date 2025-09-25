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
	public void test() {
		assertEquals(1, 1);
	}
}	
