import java.io.BufferedReader;
import java.io.IOException;

/**
 * Game board
 * Origin is in the upper left corner and x_max, y_max in the lower right.
 */
public class Board {
   
   private final Tile[][] tiles;

   private Board(Tile[][] tiles) {
      this.tiles = tiles;
   }

   public Tile getTileAt(int x, int y) {
      if((x >= 0) && (x < getWidth()) && (y >= 0) && (y < getHeight())) {
         return tiles[y][x];
      }
      
      return Tile.OUT_OF_BOUNDS;
   }
   
   public static Board createInstance(int height, int width, BufferedReader in) throws IOException {
      Tile[][] tiles = new Tile[height][width];
      for(int y = 0; y < height; y++) {
         String row = in.readLine();
         if(row == null) {
            return null; // EOF == Game Over
         }
         
         for(int x = 0; x < row.length(); x++) {
            tiles[y][x] = charToTile(row.charAt(x));
         }
      }

      return new Board(tiles);
   }

   private static Tile charToTile(char c) {
      switch(c) {
      case '#': return Tile.WALL;
      case '+': return Tile.FORCE_FIELD;
      case '.': return Tile.FLOOR;
      default:  throw new InputException("Unrecognized board tile: " + c);
      }
   }

   public int getHeight() {
      return tiles.length;
   }
   
   public int getWidth() {
      return (tiles.length > 0) ? tiles[0].length : 0;
   }
}
