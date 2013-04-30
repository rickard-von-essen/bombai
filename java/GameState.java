
public class GameState {   
   public final Board board;
   public final Players alivePlayers;
   public final Bombs bombs;
   
   GameState(Board board, Players alivePlayers, Bombs bombs) {
      this.board = board;
      this.alivePlayers = alivePlayers;
      this.bombs = bombs;
   }
   
   public boolean isFinished() {
      // If any of these are null it means we couldn't read them. Assume game over.
      return (board == null) || (alivePlayers == null) || (bombs == null);
   }

}
