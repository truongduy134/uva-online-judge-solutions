import java.util.Scanner;

public class Main {
	public static final String NOUN_REGEX = "(tom|jerry|goofy|mickey|jimmy|dog|cat|mouse)";
	public static final String ARTICLE_REGEX = "(a|the)";
	public static final String VERB_REGEX = "(hate|love|know|like)s*";
	public static final String ACTOR_REGEX = "(" + NOUN_REGEX + "|" + ARTICLE_REGEX + " " + NOUN_REGEX + ")";
	public static final String ACTIVE_LIST_REGEX = "((" + ACTOR_REGEX + " and )*" + ACTOR_REGEX + ")";
	public static final String ACTION_REGEX = "(" + ACTIVE_LIST_REGEX + " " + VERB_REGEX + " " +
												  ACTIVE_LIST_REGEX + ")";
	public static final String STATEMENT_REGEX = "(" + ACTION_REGEX + "( , " + ACTION_REGEX + ")*)";
													  
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		String inputStr;
		while(sc.hasNextLine())
		{
			inputStr = sc.nextLine();
			
			if(inputStr.trim().replaceAll(" +", " ").matches(STATEMENT_REGEX))
				System.out.println("YES I WILL");
			else
				System.out.println("NO I WON'T");
		}
	}
}
