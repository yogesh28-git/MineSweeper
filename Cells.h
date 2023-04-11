#ifndef Cells_HEADER
#define Cells_HEADER

enum cellState
{
    hidden,
    opened,
    marked
};

enum cellValue
{
    space,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    mine,
    invalid
};

class Cell
{
    private:
        cellValue value;
        cellState state;
        char displayChar;
        short color;

        void setDisplayChar()
        {
            switch(state)
            {
                case cellState::marked:
                    displayChar = 'M';
                    break;
                case cellState::hidden:
                    displayChar = ' ';
                    break;
                case cellState::opened:
                    switch(value)
                    {
                        case cellValue::mine: 
                            displayChar = '*';
                            color = 41;
                            break;
                        case cellValue::space:
                            displayChar = '0';
                            color = 0;
                            break;
                        case cellValue::one:
                            displayChar = '1';
                            color = 34;
                            break;
                        case cellValue::two:
                            displayChar = '2';
                            color = 32;
                            break;
                        case cellValue::three:
                            displayChar = '3';
                            color = 31;
                            break;
                        case cellValue::four:
                            displayChar = '4';
                            color = 35;
                            break;
                        case cellValue::five:
                            displayChar = '5';
                            color = 33;
                            break;
                        case cellValue::six:
                            displayChar = '6';
                            color = 36;
                            break;
                        case cellValue::seven:
                            displayChar = '7';
                            color = 90;
                            break;
                        case cellValue::eight:
                            displayChar = '8';
                            color = 94;
                            break;
                            
                    }
                    break;
            }
        }

    public:
        //constructors
        Cell()
        {
            value = cellValue::space;
            state = cellState::hidden;
            setDisplayChar();
        }

        Cell(cellValue data)
        {
            value = data;
            state = cellState::hidden;
            setDisplayChar();
        }

        //getters
        cellValue getValue()
        {
            return value;
        }
        cellState getState()
        {
            return state;
        }
        char getDisplayChar()
        {
            return displayChar;
        }
        char getColor()
        {
            return color;
        }

        //setters
        void setValue(cellValue data)
        {
            value = data;
            setDisplayChar();
        }
        void setState(cellState st)
        {
            state = st;
            setDisplayChar();
        }
};

#endif