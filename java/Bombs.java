import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


public class Bombs {

   private final List<Bomb> bombs;

   private Bombs(List<Bomb> bombs) {
      this.bombs = bombs;
   }

   public static Bombs createInstance(BufferedReader in) throws IOException {
      String bombCountString = in.readLine();
      if(bombCountString == null) {
         return null; // EOF == Game Over
      }
      
      int bombCount = Integer.parseInt(bombCountString.trim());
      List<Bomb> bombs = new ArrayList<Bomb>();
      for(int i = 0; i < bombCount; i++) {
         String[] bombValues = in.readLine().trim().split("\\s+");
         int playerId = Integer.parseInt(bombValues[0]);
         int x = Integer.parseInt(bombValues[1]);
         int y = Integer.parseInt(bombValues[2]);
         int ticksLeft = Integer.parseInt(bombValues[3]);
         bombs.add(new Bomb(playerId, ticksLeft, x, y));
      }

      return new Bombs(bombs);
   }

   public List<Bomb> getAllBombs() {
      return new ArrayList<Bomb>(bombs);
   }

   public List<Bomb> getBombsAt(int x, int y) {
      // Not the quickest implementation, optimize if used heavily 
      List<Bomb> bombsAtPos = new ArrayList<Bomb>();
      for(Bomb bomb : bombs) {
         if((bomb.x == x) && (bomb.y == y)) {
            bombsAtPos.add(bomb);
         }
      }

      return bombsAtPos;
   }

   public List<Bomb> getBombsWithTicksLeft(int ticksLeft) {
      // Not the quickest implementation, optimize if used heavily 
      List<Bomb> bombsAtPos = new ArrayList<Bomb>();
      for(Bomb bomb : bombs) {
         if(bomb.ticksLeft == ticksLeft) {
            bombsAtPos.add(bomb);
         }
      }

      return bombsAtPos;
   }

   public List<Bomb> getBombsForPlayer(int playerId) {
      List<Bomb> playersBombs = new ArrayList<Bomb>();
      for(Bomb bomb : bombs) {
         if(bomb.playerId == playerId) {
            playersBombs.add(bomb);
         }
      }

      return playersBombs;
   }
}
