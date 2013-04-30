import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Simple, and not very smart, implementation of a Bombai client.
 */
public class RandomEngine implements Engine {
   private final int playerId;
   private final Random random;
   private final Logger log;
   private int roundCount;
      
   public RandomEngine(int playerId, int maxTurns, Random random, Logger log) {
      // Don't care about the maximum number of turns in this implementation
      this.playerId = playerId;
      this.random = random;
      this.log = log;
      this.roundCount = 1;
   }

   public Command playRound(GameState state, RoundInfo previousActions) {
      // We don't make any use of last rounds actions in this simple client
      Player me = state.alivePlayers.getPlayerWithId(playerId);
      
      // Build a list of possible commands
      List<Command> possibleCommands = new ArrayList<Command>();
      
      // Doing nothing is always an option
      possibleCommands.add(SimpleCommand.PASS);
      
      // Add possible moves
      if(canMoveTo(state, me.x,     me.y + 1)) { possibleCommands.add(SimpleCommand.MOVE_DOWN);  }
      if(canMoveTo(state, me.x,     me.y - 1)) { possibleCommands.add(SimpleCommand.MOVE_UP);    }
      if(canMoveTo(state, me.x - 1, me.y    )) { possibleCommands.add(SimpleCommand.MOVE_LEFT);  }
      if(canMoveTo(state, me.x + 1, me.y    )) { possibleCommands.add(SimpleCommand.MOVE_RIGHT); }
      
      // Placing a bomb is also an option if we haven't already placed too many that have not yet detonated
      if(state.bombs.getBombsForPlayer(playerId).size() < BombCommand.MAX_BOMBS) {
         int tickRange = BombCommand.MAX_TICKS - BombCommand.MIN_TICKS + 1;
         possibleCommands.add(new BombCommand(BombCommand.MIN_TICKS + random.nextInt(tickRange)));
      }
      
      // Select an command
      Command command = possibleCommands.get(random.nextInt(possibleCommands.size()));
      log.debug("Player " + playerId + ", round " + roundCount + ", command " + command.getRepresentation());
      roundCount++;
      
      return command;
   }

   private boolean canMoveTo(GameState state, int x, int y) {
      return (state.board.getTileAt(x, y) == Tile.FLOOR) && state.bombs.getBombsAt(x, y).isEmpty();
   }
}
