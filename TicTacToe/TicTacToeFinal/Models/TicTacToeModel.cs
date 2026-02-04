using System.ComponentModel.DataAnnotations;

namespace TicTacToeFinal.Models
{
    public class TicTacToeModel
    {
        [Required]
        [StringLength(1, MinimumLength = 1)]
        public String Turn { get; set; } = "X";
        [Required]
        [StringLength(11, MinimumLength = 11)]
        public String Board { get; set; } = ".         ."; // board is represented by a string starting and ending with a period (to prevent trailing spaces from being cut in transit)
        public String Winner => GetWinner();
        public bool HasWinner => !String.IsNullOrWhiteSpace(GetWinner());

        // returns the owner of a given space on the board ("X" or "O", or " " for unowned)
        // board is labeled left to right, top to bottom
        public String GetOwner(int ind)
        {
            if (1 <= ind && ind <= 9)
            {
                return Board.Substring(ind, 1);
            }

            return " ";
        }

        // returns "X" if X wins, "O" if O wins, "T" if the game is a tie, or " " if the game hasn't ended
        public String GetWinner()
        {
            if (Board == null) { return " "; }

            for (int i = 1; i < 4; i++) // check rows
            { // 3*(i-1) = 0,3,6; + 1 = 1,4,7 (start of rows); +1/2 = 2/3,5/6,8/9 (others in rows)
                if (!String.IsNullOrWhiteSpace(GetOwner(3 * (i - 1) + 1)) && Board[3*(i-1) + 1] == Board[(3* (i - 1)) + 2] && Board[3 * (i - 1) + 1] == Board[(3 * (i - 1)) + 3]) 
                {
                    return GetOwner(3 * (i - 1) + 1);
                }
            }

            for (int i = 1; i < 4; i++) // check columns
            {
                if (!String.IsNullOrWhiteSpace(GetOwner(i)) && Board[i] == Board[i + 3] && Board[i] == Board[i + 6])
                {
                    return GetOwner(i);
                }
            }

            if (!String.IsNullOrWhiteSpace(GetOwner(1)) && Board[1] == Board[5] && Board[1] == Board[9]) //  \ diagonal
            {
                return GetOwner(1);
            }

            if (!String.IsNullOrWhiteSpace(GetOwner(3)) && Board[3] == Board[5] && Board[3] == Board[7]) //  / diagonal
            {
                return GetOwner(3);
            }

            for (int i = 1; i < 10; i++) // if there are any empty spaces left, no winner
            {
                if (String.IsNullOrWhiteSpace(GetOwner(i)))
                {
                    return " ";
                }
            }

            return "T"; // otherwise, tie
        }

        // if provided the index of an unclaimed tile, will give the tile to the player who's turn it is and
        // cycle turn to the next player
        public void MakeMove(int ind)
        {
            if (1 <= ind && ind <= 9)
            {
                if (String.IsNullOrWhiteSpace(GetOwner(ind)))
                { // https://stackoverflow.com/questions/8987141/how-to-change-1-char-in-the-string
                    char[] cBoard = Board.ToCharArray();
                    cBoard[ind] = Turn[0];
                    Board = String.Join("", cBoard);

                    if (Turn == "X")
                    {
                        Turn = "O";
                    } else
                    {
                        Turn = "X";
                    }
                }
            }
        }
    }
}
