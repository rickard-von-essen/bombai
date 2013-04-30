import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


public class Players {

   private final List<Player> players;

   private Players(List<Player> players) {
      this.players = players;
   }
   
   public List<Player> getAllPlayers() {
      return new ArrayList<Player>(players);
   }
   
   public List<Player> getPlayersAt(int x, int y) {
      // Not the quickest implementation, optimize if used heavily 
      List<Player> playersAtPos = new ArrayList<Player>();
      for(Player player : players) {
         if((player.x == x) && (player.y == y)) {
            playersAtPos.add(player);
         }
      }
      
      return playersAtPos;
   }

   public static Players createInstance(BufferedReader in) throws NumberFormatException, IOException {
      String alivePlayerCountString = in.readLine();
      if(alivePlayerCountString == null) {
         return null; // EOF == Game Over
      }
      
      int alivePlayerCount = Integer.parseInt(alivePlayerCountString.trim());
      List<Player> players = new ArrayList<Player>();
      for(int i = 0; i < alivePlayerCount; i++) {
         String[] playerValues = in.readLine().trim().split("\\s+");
         int id = Integer.parseInt(playerValues[0]);
         int x = Integer.parseInt(playerValues[1]);
         int y = Integer.parseInt(playerValues[2]);
         players.add(new Player(id, x, y));
      }
      
      return new Players(players);
   }

   public Player getPlayerWithId(int playerId) {
      for(Player player : players) {
         if(player.id == playerId) {
            return player;
         }
      }

      return null;
   }
}
