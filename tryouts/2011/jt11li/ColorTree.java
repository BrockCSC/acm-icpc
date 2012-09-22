import java.util.Scanner;

public class ColorTree
{
  int time = 1, currentCost = 0; 
  int numNodes = 0, firstNodeNum = 0;
  Node[] nodes; 
  //stores the current node that is being processed 
  Node currentNode = new Node(); 
  
  public static void main (String[] args)
  {
    ColorTree colorTree = new ColorTree(); 
  }
  
  public ColorTree()
  {
    //-----START-----
    
    //get input from user
    getInput();
    
    nodes = new Node[numNodes]; 
    currentNode = nodes[0]; 
    
    color(); 
  }
  
  public void getInput()
  {
    Scanner scanner = new Scanner(System.in); 
    
    numNodes = scanner.nextInt(); 
    firstNodeNum = scanner.nextInt(); 
    //get node color costs
    for (int i = 0; i < numNodes; i ++)
    {
      //set variables for nodes
      nodes[i] = new Node(); 
      nodes[i].colorCost = scanner.nextInt();   
      nodes[i].number = i + firstNodeNum; 
    }
    
  }
  
  public void color()
  {
    int[] lowestCosts = new int[numNodes]; 
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].isActive)
      {
        lowestCosts[i] = getLowestColorCost(currentNode); 
      }
    }
  }
  
  //gets lowest child color cost
  public int getLowestColorCost(Node fatherNode)
  { 
      //get the child nodes and the cost of each of those child nodes
      Node[] childNodes = currentNode.childNodes; 
      int numChild = childNodes.length; 
      
      int[] colorCost_child = new int[numChild]; 
      for (int i = 0; i < numChild; i ++)
      {
        colorCost_child[i] = childNodes[i].colorCost; 
      }
      
      //get lowest cost
      int lowest = 501; 
      for (int i = 0; i < numChild; i++)
      {
        if (colorCost_child[i] < lowest)
        {
          lowest = colorCost_child[i]; 
        }
      }
      
      return lowest;     
  }
}