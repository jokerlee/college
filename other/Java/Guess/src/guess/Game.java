/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package guess;

import java.util.Random;

/**
 *
 * @author jackal
 */
public class Game {
    Game() {
        _answer = 0;
        _count = 0;
        _rand = new Random();
        _min = 0;
        _max = 10000;
    }

    public void newGame() {
        _count = 0;
        _answer = (_min + _rand.nextLong()) % _max;
        if (_answer < 0) _answer *= -1;
    }

    public long Guess(long num) {
        _count ++;
        return num -_answer;
    }

    public long getAnswer() {
        return _answer;
    }

    public long getCount() {
        return _count;
    }

    private Random _rand;

    private long _count;

    private long _answer;

    private long _max;

    private long _min;

}
