class c_driver
{
private:
	
public:

	auto initialize( const int process_id ) -> bool
	{

		return true;
	}

	// ADD YOUR DRIVER HERE <<<

	auto get_module_base( const std::string module_name ) -> const std::uintptr_t
	{
		return true;
	}

	auto find_signature( const std::uintptr_t base, const std::string signature ) -> std::uintptr_t
	{
		return true;
	}

	auto read( const std::uintptr_t address, void *buffer, const std::size_t size ) -> bool
	{
		return true;
	}

	template <typename t>
	auto read( const std::uintptr_t address ) -> t
	{
		t response{ };
		this->read( address, &response, sizeof( t ) );
		return response;
	}

	template<typename t>
	auto read_chain( const std::uintptr_t address, const std::vector<std::uintptr_t> chain ) -> t
	{
		auto current = address;

		for ( int i = 0; i < chain.size( ) - 1; i++ )
		{
			current = this->read<std::uintptr_t>( current + chain[i] );
		}
		return this->read<t>( current + chain[chain.size( ) - 1] );
	};

	auto write( const std::uintptr_t address, void *buffer, const std::size_t size ) -> bool
	{
		return true;
	}

	template <typename t>
	auto write( const std::uintptr_t address, t value ) -> bool
	{
		return this->write( address, &value, sizeof( t ) );
	}

	auto unload( ) -> bool
	{
		
		return true;
	}
};

static c_driver *driver = new c_driver( );