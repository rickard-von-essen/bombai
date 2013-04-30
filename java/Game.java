import java.io.BufferedReader;
import java.io.IOException;


public class Game {
   private final BufferedReader in;
   private final int width;
   private final int height;
   private final int numberOfPlayers;

   public Game(int width, int height, int numberOfPlayers, BufferedReader in) {
      this.width = width;
      this.height = height;
      this.numberOfPlayers = numberOfPlayers;
      this.in = in;
   }

   public GameState getNextState() throws IOException {
      Board board = Board.createInstance(height, width, in);
      Players players = Players.createInstance(in);
      Bombs bombs = Bombs.createInstance(in);
      return new GameState(board, players, bombs);
   }

   public RoundInfo getLastRoundsActions() throws IOException {
      return RoundInfo.createInstance(numberOfPlayers, in);
   }

}
