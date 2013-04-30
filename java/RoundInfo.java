import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Provides a summary of the actions taken in a round.
 */
public class RoundInfo {
   private static final String DEAD_REPRESENTATION = "out";
   
   public final List<Integer> deadPlayerIds;
   public final List<BombAction> bombActions;
   public final List<SimpleAction> simpleActions;
   
   private RoundInfo(List<Integer> deadPlayerIds, List<BombAction> bombActions, List<SimpleAction> simpleActions) {
      this.deadPlayerIds = deadPlayerIds;
      this.bombActions = bombActions;
      this.simpleActions = simpleActions;
   }
      
   public static RoundInfo createInstance(int numberOfPlayers, BufferedReader in) throws IOException {
      List<Integer> deadPlayerIds = new ArrayList<Integer>();
      List<BombAction> bombActions = new ArrayList<BombAction>();
      List<SimpleAction> simpleActions = new ArrayList<SimpleAction>();

      for(int i = 0; i < numberOfPlayers; i++) {
         String[] actionValues = in.readLine().trim().split("\\s+");
         int playerId = Integer.parseInt(actionValues[0]);
         String action = actionValues[1]; 
         
         if(DEAD_REPRESENTATION.equalsIgnoreCase(action)) {
            deadPlayerIds.add(playerId);
         } else if(SimpleCommand.fromRepresentation(action) != null) {
            simpleActions.add(new SimpleAction(playerId, SimpleCommand.fromRepresentation(action)));
         } else {
            int ticks = Integer.parseInt(action);
            bombActions.add(new BombAction(playerId, new BombCommand(ticks)));
         }
      }
      
      return new RoundInfo(deadPlayerIds, bombActions, simpleActions);
   }

}
