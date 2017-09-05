using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Snakes_and_Ladders
{
    class PlayerClass
    {
            private string _name;
            private int _position;
            private int _number;
            private bool _skipTurn;
                                    
            public PlayerClass()
            {
                resetPlayer();
            }

            public string Name
            {
                get { return _name; }
                set { _name = value; }
            }

            public int Position
            {
                get { return _position; }
                set { _position = value; }
            }

            public int Number
            {
                get { return _number; }
                set { _number = value; }
            }

            public bool skipTurn
            {
                get { return _skipTurn; }
                set { _skipTurn = value; }
            }    

            public void resetPlayer()
            {
                _name = "Player";
                _position = 1;               
            }
        
    }
}
