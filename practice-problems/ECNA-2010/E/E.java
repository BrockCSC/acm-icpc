/**
 * Solution to Polar Bear
 * 9/27/10
 * m = number of "rings", n = number of "cells" per ring
 */

import java.util.*;

public class PolarBear {
  public static int mrings, ncells;
  public static int caseNum;
  public static int grid[][];
  public static int minr, minc, maxr, maxc;
  public static Scanner in;

  public static void main(String[] args) {
    in = new Scanner(System.in);
    caseNum = 0;
    while (true) {
      mrings = in.nextInt();
      ncells = in.nextInt();
      if (mrings == 0 && ncells == 0)
        break;
      caseNum++;
      grid = new int[mrings][ncells]; //row = ring; col = cell
      for (int i = 0; i < mrings; i++) {
        Arrays.fill(grid[i],0);
      }
      int k = in.nextInt();
      minr = mrings+1; minc = ncells+1;
      maxr = maxc = -1;
      for (int i = 0; i < k; i++) {
        int r = in.nextInt();
        int c = in.nextInt();
        if (grid[r][c] == 1)
          System.out.println("Case " + caseNum + " duplicate: " + r + " " + c);
        grid[r][c] = 1;

        if (r < minr || r == minr && c <= minc) {
           minr = r; minc = c;
        }
        if (r > maxr || r == maxr && c >= maxc) {
           maxr = r; maxc = c;
        }
      }
      int gen = in.nextInt();
//      display();
      for (int z = 0; z < gen; z++) {
        evolve();
//         display();
      }
      int total = 0;
      for (int i = 0; i < mrings; i++)
        for (int j = 0; j < ncells; j++)
          total += grid[i][j];
      System.out.printf("Case %d: %d %d %d %d %d\n",caseNum,total,
            minr,minc,maxr,maxc);
    }
  }

  public static void display() {
    for (int i = 0; i < mrings; i++) {
      for (int j = 0; j < ncells; j++) {
        System.out.print(grid[i][j]);
      }
      System.out.println();
    }
    System.out.println();
  }

  public static void evolve() {
    int newgrid[][] = new int[mrings][ncells];
    minr = mrings+1; minc = ncells+1;
    maxr = maxc = -1;
    for (int i = 0; i < mrings; i++) {
      for (int j = 0; j < ncells; j++) {
        int count = 0;
        count += grid[i][(j+1)%ncells];   // left
        count += grid[i][(j-1+ncells)%ncells]; // right
        // "above":
        if (i == 0) { // three opposite, outer ring
          count += grid[i][(j+ncells/2)%ncells];
          count += grid[i][(j+ncells/2+1)%ncells];
          count += grid[i][(j+ncells/2-1+ncells)%ncells];
        }
        else {
          count += grid[i-1][j];
          count += grid[i-1][(j+1)%ncells];
          count += grid[i-1][(j-1+ncells)%ncells];
        }

        // "below":
        if (i == mrings-1) { // three opposite, inner ring
          count += grid[i][(j+ncells/2)%ncells];
          count += grid[i][(j+ncells/2+1)%ncells];
          count += grid[i][(j+ncells/2-1+ncells)%ncells];
        }
        else {
          count += grid[i+1][j];
          count += grid[i+1][(j+1)%ncells];
          count += grid[i+1][(j-1+ncells)%ncells];
        }
        if (grid[i][j] == 1) {
          if (count == 2 || count == 3) 
            newgrid[i][j] = 1;
          else
            newgrid[i][j] = 0;
        }
        else {
          if (count == 3)
            newgrid[i][j] = 1;
          else
            newgrid[i][j] = 0;
        }
        if (newgrid[i][j] == 1) {
          if (i < minr || i == minr && j <= minc) {
             minr = i; minc = j;
          }
          if (i > maxr || i == maxr && j >= maxc) {
             maxr = i; maxc = j;
          }
        }
      }
    }

    for (int i = 0; i < mrings; i++) {
      for (int j = 0; j < ncells; j++) {
        grid[i][j] = newgrid[i][j];
      }
    }
    if (minr >= mrings || minc >= ncells) {
      minr = minc = -1;
    }
  }
}
