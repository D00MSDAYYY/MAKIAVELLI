

class Player_Client;

class Player_GUI
{
	private:
		Player_Client *_player_client;

	public:
		Player_GUI(Player_Client *player_client = nullptr) { _player_client = player_client; }
};