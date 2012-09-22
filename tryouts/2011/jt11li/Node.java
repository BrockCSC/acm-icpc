public class Node
{
  public int number, colorCost;
  public Node fatherNode;
  public Node[] childNodes; 
  //this is if they have all son nodes are colored 
  public boolean isActive = true, isColored = false; 
}