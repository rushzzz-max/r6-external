#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "driver.h"
#include "utils.h"
#include "ROL.h"



auto main( ) -> std::int32_t
{
	driver->initialize( utils::get_process_id( L"RainbowSix.exe" ) );
	const auto base = driver->get_module_base( "RainbowSix.exe" );

	// Get the game_manager one time. 
	const auto game_manager = __ROL8__( driver->read<std::uintptr_t>( base + 0x8CA45B8 ) - 0x18E83FAE4211D090i64  ^ 0xB4A4B94B8538E9C0ui64, 5 );


	while ( true )
	{
		// Entitylist
		const auto list = __ROL8__ ( ( driver->read<std::uintptr_t>( game_manager + 0x120 ) ^ 0x6Ei64 ) + 0x2D3008420A01289Fi64, 0x1D);
		const auto count = static_cast<std::uintptr_t>( __ROL8__ ( ( driver->read<std::uintptr_t>( game_manager + 0x128 ) ^ 0x6Ei64 ) + 0x2D3008420A01289Fi64, 0x1D ) );

		for ( auto i = 0u; i < count; ++i )
		{
			// Entityloop
			const auto entity = driver->read<std::uintptr_t>( list + ( i * 0x08 ) );
			const auto pawn = ( ( driver->read<std::uintptr_t>( entity + 0x38 ) - 0x2Di64 ) ^ 0x47 ) - 0x1CAC0E689A643359i64;
			const auto actor = ( ( driver->read<std::uintptr_t>( pawn + 0x18i64 ) ^ 0xD2EBEAA4B5728AEEui64 ) - 0x11175121A36679Ei64 ) ^ 0xDED4294E880D1C70ui64;

			if ( i == 0 ) // 0 = localplayer
			{
				// Simple Localplayer check 
			}
			else
			{
				const auto glow_component = __ROL8__( __ROL8__( driver->read<std::uintptr_t>( actor + 0x1c8 ), 0x1D ) + 0xCE2E924B2644A463, 0x29 ); // Glow Component
				driver->write<std::uintptr_t>( glow_component + 0xB0, 0x20748000); // Glow Overwrite 
			}
		}

		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) ); 
	}
}