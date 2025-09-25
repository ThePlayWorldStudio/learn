import org.junit.Test;
import org.junit.Before;
import org.junit.After;
import static org.junit.Assert.assertEquals;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class Tests{
	@Test
	public void coords(String[] args) {
		Vector vector = new Vector(1, 2, 3);
		
		private double[] excepted = new double[3];
		excepted[0] = 1;
		excepted[1] = 2;
		excepted[2] = 3;
		assertEquals(excepted, vector.Coords());
		
	}
}	
