/* Solution to Vampires */
import java.util.*;

public class Vampires {
  public static Scanner in;
  public static String room[][];
  public static int v, o, m;
  public static int caseNum;
  public static int locx[], locy[];

  public static void main(String[] args) {
    in = new Scanner(System.in);
    caseNum = 0;

    while (true) {
      v = in.nextInt();
      o = in.nextInt();
      m = in.nextInt();
      if (v == 0 && o == 0 && m == 0) break;
      caseNum++;
      room = new String[101][101];
      locx = new int[v];
      locy = new int[v];
      for (int i = 0; i <= 100; i++)
        Arrays.fill(room[i],".");

      for (int i = 0; i < v; i++) {
        int x = in.nextInt();
        int y = in.nextInt();
        room[x][y] = ""+(i+1);
        locx[i] = x;
        locy[i] = y;
      }
      for (int i = 0; i < o; i++) {
        int x = in.nextInt();
        int y = in.nextInt();
        room[x][y] = "h";
      }
      for (int i = 0; i < m; i++) {
        String dir = in.next();
        int x1 = in.nextInt();
        int y1 = in.nextInt();
        int x2 = in.nextInt();
        int y2 = in.nextInt();
        char c = "^v><".charAt("NSEW".indexOf(dir.charAt(0)));
        if (x1 > x2) {int temp = x1; x1 = x2; x2 = temp;}
        if (y1 > y2) {int temp = y1; y1 = y2; y2 = temp;}
        if (c == '^' || c == 'v') {
           for (int j = x1; j <= x2; j++)
             room[j][y1] = ""+c;
        }
        else {
           for (int j = y1; j <= y2; j++)
             room[x1][j] = ""+c;
        }
      }
      System.out.println("Case " + caseNum + ":");
// display();
      solve();
    }

  }

  public static void solve() {
    String ans = "";
    boolean haveAns = false;
    for (int j = 0; j < v; j++) {
      ans = "";
      int x = locx[j];
      int y = locy[j];
      // east:
      int i = x+1;
      while (i <= 100 && room[i][y] != "h" && "^v><".indexOf(room[i][y]) < 0)
        i++;
      if (i <= 100 && room[i][y].equals("<")){
        ans += "east ";
      }
      // north:
      i = y+1;
      while (i <= 100 && room[x][i] != "h" && "^v><".indexOf(room[x][i]) < 0)
        i++;
      if (i <= 100 && room[x][i].equals("v")){
        ans += "north ";
      }
      // south:
      i = y-1;
      while (i >= 0 && room[x][i] != "h" && "^v><".indexOf(room[x][i]) < 0)
        i--;
      if (i >= 0 && room[x][i].equals("^")){
        ans += "south ";
      }
      // west:
      i = x-1;
      while (i >= 0 && room[i][y] != "h" && "^v><".indexOf(room[i][y]) < 0)
        i--;
      if (i >= 0 && room[i][y].equals(">")){
        ans += "west ";
      }
      ans = ans.trim();
      if (ans.length() > 0) {
        System.out.println("vampire " + (j+1) + " " + ans);
		haveAns = true;
      }
    }
    if (!haveAns)
      System.out.println("none");
  }


  public static void display() {
     for (int j = 24; j >= 0; j--) {
       for (int i = 0; i < 25; i++) {
         System.out.print(room[i][j]);
       }
       System.out.println();
     }
  }
}
