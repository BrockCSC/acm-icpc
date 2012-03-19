// Solution to Flip It

import java.util.*;

public class Flip {
  public static int n,m;
  public static Stack grid[][];
  public static Scanner in;
  public static int caseNum;

  public static void main(String[] args) {
    in = new Scanner(System.in);
    caseNum = 0;
    while(true) {
      n = in.nextInt();
      m = in.nextInt();
      if (m == 0 && n == 0) break;
      caseNum++;
      grid = new Stack[n][m];
      int top = 0, bottom = n-1, left = 0, right = m-1;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          grid[i][j] = new Stack();
      for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
          grid[i][j].push(in.nextInt());
      if (m>1 || n > 1) {
        String dir = in.next();
        for (int j = 0; j < dir.length(); j++) {
          char c = dir.charAt(j);
          switch(c) {
            case 'T': for (int i = left; i <= right; i++) {
                        while(!grid[top][i].empty()) {
                          int temp = (Integer)(grid[top][i].pop());
                          grid[top+1][i].push(-temp);
                        }
                      }
                      top++;
                      break;
            case 'B': for (int i = left; i <= right; i++) {
                        while(!grid[bottom][i].empty()) {
                          int temp = (Integer)(grid[bottom][i].pop());
                          grid[bottom-1][i].push(-temp);
                        }
                      }
                      bottom--;
                      break; case 'L': for (int i = top; i <= bottom; i++) {
                        while(!grid[i][left].empty()) {
                          int temp = (Integer)(grid[i][left].pop());
                          grid[i][left+1].push(-temp);
                        }
                      }
                      left++;
                      break;
            case 'R': for (int i = top; i <= bottom; i++) {
                        while(!grid[i][right].empty()) {
                          int temp = (Integer)(grid[i][right].pop());
                          grid[i][right-1].push(-temp);
                        }
                      }
                      right--;
                      break;
          }
        }
      }
      System.out.print("Case " + caseNum + ":");
      print(grid[top][left]);
      System.out.println();
    }
  }

  public static void print(Stack<Integer> s) {
    if (s.empty()) return;
    int i = s.pop();
    print(s);
    if (i > 0)
      System.out.print(" "+i);
  }
}
