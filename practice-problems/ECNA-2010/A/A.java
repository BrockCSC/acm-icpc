import java.util.Scanner;

public class Triangles
{
	public static final int MAX = 20;
	public static matches [] holeMatches = new matches[MAX];
	public static triangle [] hole = new triangle[MAX];
	public static triangle [] piece = new triangle[2*MAX];
	public static line [] lines2 = new line[6*MAX];
	public static int n;

	public static double cosine(point p1, point p2, point p3)
	// determine cosine between line formed from (p1,p2) and (p2,p3)
	{
		point pa = p1.sub(p2);
		point pb = p3.sub(p2);
		double lena = Math.sqrt(pa.x*pa.x + pa.y*pa.y);
		double lenb = Math.sqrt(pb.x*pb.x + pb.y*pb.y);
		return (pa.x*pb.x + pa.y*pb.y)/lena/lenb;
	}

	public static int findFit(double len1, double len2, double len3, int start)
	// check if a given set of lengths matches a triangle hole, starting at
	//  hole start
	{
		double [] len = new double[3];
		len[0] = len1;
		len[1] = len2;
		len[2] = len3;
		if (len[1] < len[0]) {
			double tmp = len[0];
			len[0] = len[1];
			len[1] = tmp;
		}
		if (len[2] < len[0]) {
			double tmp = len[0];
			len[0] = len[2];
			len[2] = tmp;
		}
		if (len[2] < len[1]) {
			double tmp = len[2];
			len[2] = len[1];
			len[1] = tmp;
		}
		for(int i=start; i<n; i++) {
			if (Math.abs(len[0] - hole[i].lens[0]) <= 0.01 &&
			    Math.abs(len[1] - hole[i].lens[1]) <= 0.01 &&
			    Math.abs(len[2] - hole[i].lens[2]) <= 0.01 && !hole[i].used)
				return i;
		}
		return -1;
	}

	public static int foundMatch(int i1, int i2, int start)
	// check if two triangle pieces can be put together to match a triangle hole
	{
		triangle t1 = piece[lines2[i1].t];		// get the two pieces
		triangle t2 = piece[lines2[i2].t];
		if (t1.used || t2.used)
			return -1;
		int v1 = lines2[i1].v;
		int v2 = lines2[i2].v;
										// check one end to see if the angles
										//   add up to 180
		double cos1 = cosine(t1.p[(v1+2)%3], t1.p[v1], t1.p[(v1+1)%3]);
		double cos2 = cosine(t2.p[v2], t2.p[(v2+1)%3], t2.p[(v2+2)%3]);
		if (Math.abs(cos1+cos2) <= 0.01) {
			int t;
			if ((t = findFit(t1.lens[(v1+1)%3], t1.lens[(v1+2)%3]+t2.lens[(v2+1)%3], t2.lens[(v2+2)%3], start)) != -1) {
				return t;
			}
		}
										// now check the other end
		cos1 = cosine(t2.p[(v2+2)%3], t2.p[v2], t2.p[(v2+1)%3]);
		cos2 = cosine(t1.p[v1], t1.p[(v1+1)%3], t1.p[(v1+2)%3]);
		if (Math.abs(cos1+cos2) <= 0.01) {
			int t;
			if ((t = findFit(t2.lens[(v2+1)%3], t2.lens[(v2+2)%3]+t1.lens[(v1+1)%3], t1.lens[(v1+2)%3], start)) != -1) {
				return t;
			}
		}
		return -1;
	}

	public static void findMatches(int n)
	{
		int t;
		for(int i=0; i<6*n; i++) {
			int j=i+1;
									// check for two side lengths that match...
			while(j<6*n && (Math.abs(lines2[i].length - lines2[j].length) < 0.01)) {
				if (lines2[i].t == lines2[j].t) { 		// ...and not it same triangle...
					j++;
					continue;
				}
				int start = 0;
				while ((t = foundMatch(i,j,start)) != -1) {		// ...and see if they can be combined to match a hole
					holeMatches[t].matches[holeMatches[t].nMatch].t1 = lines2[i].t;
					holeMatches[t].matches[holeMatches[t].nMatch].t2 = lines2[j].t;
					holeMatches[t].nMatch++;
					start = t+1;								// try again looking for another hole
				}
				j++;
			}
		}
	}

	public static void removeTriangles(int t, int n)
	{
		for(int i=0; i<n; i++) {
			int nMatch = holeMatches[i].nMatch;
			for(int j=0; j<nMatch; j++) {
				if (holeMatches[i].matches[j].t1 == t || holeMatches[i].matches[j].t2 == t) {
					holeMatches[i].matches[j].t1 = holeMatches[i].matches[nMatch-1].t1;
					holeMatches[i].matches[j].t2 = holeMatches[i].matches[nMatch-1].t2;
					nMatch--;
				}
			}
			holeMatches[i].nMatch = nMatch;
		}
	}
	
	public static boolean findSolution(int n)
	{
		int count = 0;
		while (count < n) {
			for(int i=0; i<n; i++) {
				if (hole[i].used || holeMatches[i].nMatch > 1)
					continue;
				if (holeMatches[i].nMatch == 0)
					return false;
				hole[i].used = true;
				hole[i].pieces[0] = holeMatches[i].matches[0].t1;
				hole[i].pieces[1] = holeMatches[i].matches[0].t2;
				removeTriangles(holeMatches[i].matches[0].t1, n);
				removeTriangles(holeMatches[i].matches[0].t2, n);
				count++;
			}
		}
		return true;
	}

	public static void main(String [] args)
	{
		int icase=0;
		for(int i=0; i<MAX; i++) {
			holeMatches[i] = new matches();
			hole[i] = new triangle();
		}
		for(int i=0; i<2*MAX; i++) {
			piece[i] = new triangle();
		}
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		while (n != 0) {
			icase++;
			for(int i=0; i<n; i++) {				// read in each triangular hole...
				for(int j=0; j<3; j++) {
					hole[i].p[j].x  = in.nextDouble();
					hole[i].p[j].y  = in.nextDouble();
				}
				hole[i].makeClockwise();
				hole[i].used = false;
				holeMatches[i].nMatch = 0;
													// ... and sort sides by length
				hole[i].lens[0] = hole[i].p[0].length(hole[i].p[1]);
				hole[i].lens[1] = hole[i].p[1].length(hole[i].p[2]);
				hole[i].lens[2] = hole[i].p[2].length(hole[i].p[0]);
				if (hole[i].lens[1] < hole[i].lens[0]) {
					double tmp = hole[i].lens[1];
					hole[i].lens[1] = hole[i].lens[0];
					hole[i].lens[0] = tmp;
				}
				if (hole[i].lens[2] < hole[i].lens[0]) {
					double tmp = hole[i].lens[2];
					hole[i].lens[2] = hole[i].lens[0];
					hole[i].lens[0] = tmp;
				}
				if (hole[i].lens[2] < hole[i].lens[1]) {
					double tmp = hole[i].lens[1];
					hole[i].lens[1] = hole[i].lens[2];
					hole[i].lens[2] = tmp;
				}
			}
			for(int i=0; i<2*n; i++) {					// read in triangular pieces
				for(int j=0; j<3; j++) {
					piece[i].p[j].x = in.nextDouble();
					piece[i].p[j].y = in.nextDouble();
				}
				piece[i].makeClockwise();
				piece[i].used = false;
				piece[i].lens[0] = piece[i].p[0].length(piece[i].p[1]);
				piece[i].lens[1] = piece[i].p[1].length(piece[i].p[2]);
				piece[i].lens[2] = piece[i].p[2].length(piece[i].p[0]);
			}
												// store all side lengths of
												//   triangular pieces in sorted list
			for(int i=0; i<2*n; i++) {
				for(int j=0; j<3; j++) {
					double len = piece[i].lens[j];
					int k=3*i+j;
					while (k > 0 && lines2[k-1].length > len) {
						lines2[k] = lines2[k-1];
						k--;
					}
					lines2[k] = new line();
					lines2[k].length = len;
					lines2[k].t = i;
					lines2[k].v = j;
				}
			}
	
			findMatches(n);
			boolean solved = findSolution(n);
												// output results
			System.out.println("Case " + icase + ":");
			if (solved) {
				for(int i=0; i<n; i++) {
					System.out.print("Hole " + (i+1) + ": ");
					if (hole[i].pieces[0] < hole[i].pieces[1])
						System.out.println(hole[i].pieces[0]+1 + ", " + (hole[i].pieces[1]+1));
					else
						System.out.println(hole[i].pieces[1]+1 + ", " + (hole[i].pieces[0]+1));
				}
			}
			else {
				System.out.println("no");
			}
			n = in.nextInt();
			if (n != 0)
				System.out.println();
		}
	}
}

class point {					// simple 2-d point class
	public double x, y;
	
	public point() {						// default constructor
		x = y= 0.0;
	}

	public point(double nx, double ny)
	{
		x = nx;
		y = ny;
	}

	public point sub(point rhs) {			// translate a point by subtracting another
									//    point (vector) from it (non-mutating)
		return new point(x-rhs.x, y-rhs.y);
	}

	public double length(point p2)		// determin distance between this point and another
	{
		return Math.sqrt((x-p2.x)*(x-p2.x) + (y-p2.y)*(y-p2.y));
	}
}

class  match
{
	public int t1, t2;				// two triangles which match a hole
};

class matches
{
	public int nMatch;				// number of matches for a hole
	public match [] matches = new match[Triangles.MAX];			// the matches

	public matches()
	{
		for(int i=0; i<Triangles.MAX; i++)
			matches[i] = new match();
	}

}

class triangle {			// simple triangle class
	public point [] p = new point[3];
	public int [] pieces = new int[2];		// used only by triangle holes
	public boolean used;					// whether triangle has been matched
	public double [] lens = new double[3];	// length of sides (sorted for triangle holes)

	public triangle()
	{
		for(int i=0; i<3; i++)
			p[i] = new point();
	}

	public void makeClockwise()		// order point in clockwise fashion
	{
		int index = 0;
		for(int i=1; i<3; i++)
			if (p[i].x < p[index].x)
				index = i;
		point temp = p[0];
		p[0] = p[index];
		p[index] = temp;
		double sin1 = (p[1].y-p[0].y)/p[0].length(p[1]);
		double sin2 = (p[2].y-p[0].y)/p[0].length(p[2]);
		if (sin2 > sin1) {
			temp = p[1];
			p[1] = p[2];
			p[2] = temp;
		}
	}
}

class line {				// used to store triangle sides 
	public double length;
	public int t;				// triangle which contains the line
	public int v;				// starting vertex of line
	public boolean used;		// whether it's been matched with another line
}

