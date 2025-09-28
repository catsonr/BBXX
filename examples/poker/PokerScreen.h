#ifndef POKERSCREEN_H
#define POKERSCREEN_H

#include <BEATBOXX/ScreenState/Screen.h>

#include <stdio.h>
#include <random>

std::mt19937 rng(0);
std::uniform_real_distribution<float> random_float(0.0f, 1.0f);

enum struct Suit
{
    Hearts = 0,
    Diamonds = 1,
    Spades = 2,
    Clubs = 3
}; // Suit

enum struct Rank
{
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 10,
    Queen = 10,
    King = 10,
    Ace = 11
}; // Rank

struct Card
{
    Card() = delete;
    Card(Suit suit, Rank rank) :
        suit(suit),
        rank(rank)
    {}

    Suit suit;
    Rank rank;
}; // Card

struct Deck
{
    /* CONSTRUCTORS */

    Deck()
    {
        constexpr Suit suits[] = {
            Suit::Hearts, Suit::Diamonds, Suit::Spades, Suit::Clubs
        };
        constexpr Rank ranks[] = {
            Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six, Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten, Rank::Jack, Rank::Queen, Rank::King, Rank::Ace
        };
        
        for(Suit suit : suits)
        {
            for(Rank rank : ranks)
            {
                cards.push_back(Card {suit, rank});
            }
        }
    }
    
    /* PUBLIC MEMBERS */
    
    std::vector<Card> cards;
    
    /* PUBLIC METHODS */
    
    void print()
    {
        for(int i = 0; i < cards.size(); i++)
        {
            const Card& card = cards[i];
            printf("%i: %i of %i\n", i, card.rank, card.suit);
        }
    }

    void shuffle()
    {
        std::vector<Card> temp_deck;
        
        // move all cards in deck into temp_deck
        while( !cards.empty() )
        {
            temp_deck.push_back(cards.back());
            cards.pop_back();
        }
        
        while( !temp_deck.empty() )
        {
            float r = random_float(rng);
            int i = r * temp_deck.size();
            
            cards.push_back(temp_deck[i]);
            temp_deck[i] = temp_deck.back();
            temp_deck.pop_back();
        }
    }

}; // Deck

struct Poker
{
    Deck deck;
}; // Poker

struct PokerScreen : Screen
{
    /* CONSTRUCTORS */

    PokerScreen() = delete;
    PokerScreen(BXCTX& bxctx) :
        Screen(bxctx)
    {}
    
    /* PUBLIC MEMBERS */

    Poker poker;
    
    /* PUBLIC METHODS */
    bool init() override
    {
        poker.deck.print();
        poker.deck.shuffle();
        printf("deck shuffled!\n\n");
        poker.deck.print();
        return true;
    }

    void handle_event(const SDL_Event* event) override
    {
        if( bxctx.inputstate.key_pressed(SDL_SCANCODE_SPACE) )
        {
            printf("[PokerScreen::handle_event] fyi space got pressed\n");
        }
    }
    
    void iterate() override
    {

    }
    
    void draw() override
    {
        // do nothing, for now
    }
}; // PokerScreen

#endif // POKERSCREEN_H