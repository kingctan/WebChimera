#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "ChimeraApi.h"

////////////////////////////////////////////////////////////////////////////
/// JSAudioAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSAudioAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

unsigned JSAudioAPI::get_trackCount()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.audio().track_count();
}

bool JSAudioAPI::get_mute()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.audio().is_muted();
}

void JSAudioAPI::set_mute( bool m )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().set_mute( m );
}

unsigned int JSAudioAPI::get_volume()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.audio().get_volume();
}

void JSAudioAPI::set_volume( unsigned int vol )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().set_volume( vol );
}

int JSAudioAPI::get_track()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.audio().get_track();
}

void JSAudioAPI::set_track( int idx )
{
    if( idx < 0 )
        return;

    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().set_track( idx );
}

unsigned int JSAudioAPI::get_channel()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.audio().get_channel();
}

void JSAudioAPI::set_channel( unsigned int ch )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().set_channel( (libvlc_audio_output_channel_t) ch );
}

void JSAudioAPI::toggleMute()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().toggle_mute();
}

std::string JSAudioAPI::description( unsigned int trackID )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string track_name;

    libvlc_track_description_t* root_track_desc =
        libvlc_audio_get_track_description( p.get_mp() );
    if( !root_track_desc )
        return track_name;

    unsigned int tc = p.audio().track_count();
    if( tc && trackID < tc ) {
        libvlc_track_description_t* track_desc = root_track_desc;
        for( ; trackID && track_desc ; --trackID ){
            track_desc = track_desc->p_next;
        }

        if ( track_desc && track_desc->psz_name ) {
            track_name = track_desc->psz_name;
        }
    }
    libvlc_track_description_list_release( root_track_desc );

    return track_name;
}

////////////////////////////////////////////////////////////////////////////
/// JSInputAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSInputAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

double JSInputAPI::get_length()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>( p.current_media().get_length() );
}

double JSInputAPI::get_fps()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.current_media().get_fps();
}

bool JSInputAPI::get_hasVout()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().has_vout();
}

unsigned int JSInputAPI::get_state()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_state();
}

double JSInputAPI::get_position()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_position();
}

void JSInputAPI::set_position( double pos )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_position( static_cast<float>( pos ) );
}

double JSInputAPI::get_time()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>( p.get_time() );
}

void JSInputAPI::set_time( double t )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.set_time( static_cast<libvlc_time_t>( t ) );
}

double JSInputAPI::get_rate()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_rate();
}

void JSInputAPI::set_rate( double r )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_rate( static_cast<float>( r ) );
}

////////////////////////////////////////////////////////////////////////////
/// JSPlaylistItemsAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSPlaylistItemsAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

unsigned int JSPlaylistItemsAPI::get_count()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.item_count();
}

void JSPlaylistItemsAPI::clear()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.clear_items();
}

bool JSPlaylistItemsAPI::remove( unsigned int idx )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

   return p.delete_item( idx );
}

////////////////////////////////////////////////////////////////////////////
/// JSPlaylistAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSPlaylistAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

unsigned int JSPlaylistAPI::get_itemCount()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.item_count();
}

bool JSPlaylistAPI::get_isPlaying()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.is_playing();
}

int JSPlaylistAPI::get_current()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.current_item();
}

int JSPlaylistAPI::add( const std::string& mrl )
{
    ChimeraPtr plg = getPlugin();

    return plg->add_playlist_item( mrl.c_str() );
}

int JSPlaylistAPI::addWithOptions( const std::string& mrl,
                                   const std::vector<std::string>& options)
{
    if( options.empty() )
        return add( mrl );

    ChimeraPtr plg = getPlugin();

    return plg->add_playlist_item( mrl, options );
}

void JSPlaylistAPI::play()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.play();
}

bool JSPlaylistAPI::playItem( unsigned int idx )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.play( idx );
}

void JSPlaylistAPI::setCurrentItem( unsigned int idx )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_current( idx );
}

void JSPlaylistAPI::pause()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.pause();
}

void JSPlaylistAPI::togglePause()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    if ( p.is_playing() ) p.pause();
    else p.play();
}

void JSPlaylistAPI::stop()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    //use async stop to avoid freeze (on network timeout for example).
    p.stop( true );
}

void JSPlaylistAPI::next()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.next();
}

void JSPlaylistAPI::prev()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.prev();
}

void JSPlaylistAPI::clear()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.clear_items();
}

bool JSPlaylistAPI::removeItem( unsigned int idx )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.delete_item( idx );
}

////////////////////////////////////////////////////////////////////////////
/// JSSubtitleAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSSubtitleAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

unsigned JSSubtitleAPI::get_trackCount()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.subtitles().track_count();
}

int JSSubtitleAPI::get_track()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.subtitles().get_track();
}

void JSSubtitleAPI::set_track( int idx )
{
    if( idx < 0 )
        return;

    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.subtitles().set_track( idx );
}

std::string JSSubtitleAPI::description( unsigned int sID )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string s_name;

    libvlc_track_description_t* root_s_desc =
        libvlc_video_get_spu_description( p.get_mp() );
    if( !root_s_desc )
        return s_name;

    unsigned int sc = libvlc_video_get_spu_count( p.get_mp() );
    if( sc && sID < sc ) {
        libvlc_track_description_t* s_desc = root_s_desc;
        for( ; sID && s_desc ; --sID ){
            s_desc = s_desc->p_next;
        }

        if ( s_desc && s_desc->psz_name ) {
            s_name = s_desc->psz_name;
        }
    }
    libvlc_track_description_list_release( root_s_desc );

    return s_name;
}

////////////////////////////////////////////////////////////////////////////
/// positions
////////////////////////////////////////////////////////////////////////////
const char* positions [] = {
    "center",        // 0
    "left",          // 1
    "right",         // 2
    0,               // 3
    "top",           // 4
    "top-left",      // 5
    "top-right",     // 6
    0,               // 7
    "bottom",        // 8
    "bottom-left",   // 9
    "bottom-right",  //10
};

inline std::string get_position_by_id( unsigned int id )
{
    unsigned int p_size = sizeof( positions ) / sizeof( positions[0] );
    if( id < p_size && positions[id] ) {
        return positions[id];
    }
    else return std::string();
}

int get_id_by_position( const std::string& pos )
{
    int p_size = sizeof( positions ) / sizeof( positions[0] );
    for( int i=0; i<p_size; ++i ) {
        if( positions[i] && pos == positions[i] )
            return i;
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////
/// JSMarqueeAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSMarqueeAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

std::string JSMarqueeAPI::get_text()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string text;
    char* t = libvlc_video_get_marquee_string( p.get_mp(), libvlc_marquee_Text );
    if ( t )
        text = t;

    return text;
}

void JSMarqueeAPI::set_text( const std::string& t )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_marquee_string( p.get_mp(), libvlc_marquee_Text, t.c_str() );
}

std::string JSMarqueeAPI::get_position()
{
    int p = get_marquee_int( libvlc_marquee_Position );
    return get_position_by_id( p );
}

void JSMarqueeAPI::set_position( const std::string& position )
{
    int p = get_id_by_position( position );
    set_marquee_int( libvlc_marquee_Position, p );
}

int JSMarqueeAPI::get_marquee_int( libvlc_video_marquee_option_t o )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_marquee_int( p.get_mp(), o );
}

void JSMarqueeAPI::set_marquee_int( libvlc_video_marquee_option_t o, int i )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_marquee_int( p.get_mp(), o, i );
}

////////////////////////////////////////////////////////////////////////////
/// JSLogoAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSLogoAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

std::string JSLogoAPI::get_position()
{
    int p = get_logo_int( libvlc_logo_position );
    return get_position_by_id( p );
}

void JSLogoAPI::set_position( const std::string& position )
{
    int p = get_id_by_position( position );
    set_logo_int( libvlc_logo_position, p );
}

void JSLogoAPI::file( const std::string& f )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_logo_string( p.get_mp(), libvlc_logo_file, f.c_str() );
}

int JSLogoAPI::get_logo_int( libvlc_video_logo_option_t o )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_logo_int( p.get_mp(), o );
}

void JSLogoAPI::set_logo_int( libvlc_video_logo_option_t o, int i )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_logo_int( p.get_mp(), o, i );
}

////////////////////////////////////////////////////////////////////////////
/// JSDeinterlaceAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSDeinterlaceAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

void JSDeinterlaceAPI::enable( const std::string& mode )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_deinterlace( p.get_mp(), mode.c_str() );
}

void JSDeinterlaceAPI::disable()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_deinterlace( p.get_mp(), "" );
}

////////////////////////////////////////////////////////////////////////////
/// JSVideoAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSVideoAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

void JSVideoAPI::getVideoSize( unsigned* width, unsigned* height )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_media_t* media = libvlc_media_player_get_media( p.get_mp() );
    if( media && !libvlc_media_is_parsed( media ) )
        libvlc_media_parse( media );

    *width = *height = 0;
    libvlc_video_get_size( p.get_mp(), 0, width, height );

    if( media && ( !*width || !*height ) ) {
        /*FIXME: It's not absolutely correct way to detect media dimensions,
        since now will be returned dimensions of first track with not zero demensions,
        and there are no any guarantee it will be be current playing track.
        But we nothing can do with it, since there are no way to match current
        playing track and track info received from libvlc_media_get_tracks_info for now.*/
        libvlc_media_track_info_t* info;
        int infoCount = libvlc_media_get_tracks_info( media, &info );
        for( int i = 0; i < infoCount; ++i ) {
            if( libvlc_track_video == info[i].i_type &&
                info[i].u.video.i_width &&
                info[i].u.video.i_height )
            {
                *width = info[i].u.video.i_width;
                *height = info[i].u.video.i_height;
                break;
            }
        }
        libvlc_free( info );
    }
}

unsigned int JSVideoAPI::get_width()
{
    unsigned x = 0, y = 0;
    getVideoSize( &x, &y );

    return x;
}

unsigned int JSVideoAPI::get_height()
{
    unsigned x = 0, y = 0;
    getVideoSize( &x, &y );

    return y;
}

unsigned JSVideoAPI::get_trackCount()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().track_count();
}

int JSVideoAPI::get_track()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().get_track();
}

void JSVideoAPI::set_track( int idx )
{
    if( idx < 0 )
        return;

    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.video().set_track( idx );
}

bool JSVideoAPI::get_fullscreen()
{
    ChimeraPtr plg = getPlugin();

    return plg->is_fullscreen();
}

void JSVideoAPI::set_fullscreen( bool fs )
{
    ChimeraPtr plg = getPlugin();

    return plg->set_fullscreen( fs );
}

void JSVideoAPI::toggleFullscreen()
{
    ChimeraPtr plg = getPlugin();

    plg->toggle_fullscreen();
}

std::string JSVideoAPI::get_aspectRatio()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string aspectRatio;
    char* ar = libvlc_video_get_aspect_ratio( p.get_mp() );
    if ( ar )
        aspectRatio = ar;
    libvlc_free( ar );

    return aspectRatio;
}

void JSVideoAPI::set_aspectRatio( const std::string& ar )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_aspect_ratio( p.get_mp(), ar.c_str() );
}

int JSVideoAPI::get_subtitle()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_spu( p.get_mp() );
}

void JSVideoAPI::set_subtitle( unsigned int t )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_spu( p.get_mp(), t );
}

std::string JSVideoAPI::get_crop()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string crop;
    char* c = libvlc_video_get_crop_geometry( p.get_mp() );
    if ( c )
        crop = c;
    libvlc_free( c );

    return crop;
}

void JSVideoAPI::set_crop( const std::string& c )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_crop_geometry( p.get_mp(), c.c_str() );
}

int JSVideoAPI::get_teletext()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_teletext( p.get_mp() );
}

void JSVideoAPI::set_teletext( unsigned int t )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_set_teletext( p.get_mp(), t );
}

void JSVideoAPI::toggleTeletext()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_toggle_teletext( p.get_mp() );
}

float JSVideoAPI::get_contrast()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().get_contrast();
}

void JSVideoAPI::set_contrast( float v )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().set_contrast( v );
}

float JSVideoAPI::get_brightness()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().get_brightness();
}

void JSVideoAPI::set_brightness( float v )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().set_brightness( v );
}

float JSVideoAPI::get_hue()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().get_hue();
}

void JSVideoAPI::set_hue( float v )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().set_hue( v );
}

float JSVideoAPI::get_saturation()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().get_saturation();
}

void JSVideoAPI::set_saturation( float v )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().set_saturation( v );
}

float JSVideoAPI::get_gamma()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().get_gamma();
}

void JSVideoAPI::set_gamma( float v )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.video().set_gamma( v );
}

////////////////////////////////////////////////////////////////////////////
/// JSMediaDescAPI
////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSMediaDescAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

std::string JSMediaDescAPI::get_meta( libvlc_meta_t e_meta )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_media_t * p_media = libvlc_media_player_get_media( p.get_mp() );
    const char* info = p_media ? libvlc_media_get_meta( p_media, e_meta ) : 0;
    return info ? std::string( info ) : std::string();
}

std::string JSMediaDescAPI::get_title()
{
    return get_meta( libvlc_meta_Title );
}

std::string JSMediaDescAPI::get_artist()
{
    return get_meta( libvlc_meta_Artist );
}

std::string JSMediaDescAPI::get_genre()
{
    return get_meta( libvlc_meta_Genre );
}

std::string JSMediaDescAPI::get_copyright()
{
    return get_meta( libvlc_meta_Copyright );
}

std::string JSMediaDescAPI::get_album()
{
    return get_meta( libvlc_meta_Album );
}

std::string JSMediaDescAPI::get_trackNumber()
{
    return get_meta( libvlc_meta_TrackNumber );
}

std::string JSMediaDescAPI::get_description()
{
    return get_meta( libvlc_meta_Description );
}

std::string JSMediaDescAPI::get_rating()
{
    return get_meta( libvlc_meta_Rating );
}

std::string JSMediaDescAPI::get_date()
{
    return get_meta( libvlc_meta_Date );
}

std::string JSMediaDescAPI::get_setting()
{
    return get_meta( libvlc_meta_Setting );
}

std::string JSMediaDescAPI::get_URL()
{
    return get_meta( libvlc_meta_URL );
}

std::string JSMediaDescAPI::get_language()
{
    return get_meta( libvlc_meta_Language );
}

std::string JSMediaDescAPI::get_nowPlaying()
{
    return get_meta( libvlc_meta_NowPlaying );
}

std::string JSMediaDescAPI::get_publisher()
{
    return get_meta( libvlc_meta_Publisher );
}

std::string JSMediaDescAPI::get_encodedBy()
{
    return get_meta( libvlc_meta_EncodedBy );
}

std::string JSMediaDescAPI::get_artworkURL()
{
    return get_meta( libvlc_meta_ArtworkURL );
}

std::string JSMediaDescAPI::get_trackID()
{
    return get_meta( libvlc_meta_TrackID );
}

///////////////////////////////////////////////////////////////////////////////
/// @fn ChimeraPtr JSRootAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
ChimeraPtr JSRootAPI::getPlugin()
{
    ChimeraPtr plugin( m_plugin.lock() );
    if ( !plugin ) {
        throw FB::script_error( "The plugin is invalid" );
    }
    return plugin;
}

// Read-only property version
std::string JSRootAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

std::string JSRootAPI::get_vlcVersion()
{
    return libvlc_get_version();
}

void JSRootAPI::play( const std::string& mrl )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.clear_items();

    int item = plg->add_playlist_item( mrl.c_str() );
    if( item >= 0) {
        p.play( item );
    }
}

void JSRootAPI::pause()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.pause();
}

void JSRootAPI::togglePause()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    if ( p.is_playing() ) p.pause();
    else p.play();
}

void JSRootAPI::stop()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    //use async stop to avoid freeze ( on network timeout for example ).
    p.stop( true );
    p.clear_items();
}

void JSRootAPI::toggleMute()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().toggle_mute();
}

bool JSRootAPI::get_playing()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.is_playing();
}

double JSRootAPI::get_length()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>( p.current_media().get_length() );
}

std::string JSRootAPI::get_qmlError()
{
    ChimeraPtr plg = getPlugin();

    return plg->getQmlError();
}

std::string JSRootAPI::get_qml()
{
    ChimeraPtr plg = getPlugin();
    const vlc_player_options& o = plg->get_options();

    return o.get_qml();
}

void JSRootAPI::set_qml( const std::string& qml )
{
    ChimeraPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    o.set_qml( qml );
}

double JSRootAPI::get_position()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_position();
}

void JSRootAPI::set_position( double pos )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_position( static_cast<float>( pos ) );
}

double JSRootAPI::get_time()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>( p.get_time() );
}

void JSRootAPI::set_time( double t )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_time( static_cast<libvlc_time_t>( t ) );
}

unsigned int JSRootAPI::get_volume()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.audio().get_volume();
}

void JSRootAPI::set_volume( unsigned int v )
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.audio().set_volume( v );
}

std::string JSRootAPI::get_bgcolor()
{
    ChimeraPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    return o.get_bg_color();
}

void JSRootAPI::set_bgcolor( const std::string& bg )
{
    ChimeraPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    o.set_bg_color( bg );
}

int JSRootAPI::get_state()
{
    ChimeraPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_state();
};

bool JSRootAPI::get_fullscreen()
{
    ChimeraPtr plg = getPlugin();

    return plg->is_fullscreen();
}

void JSRootAPI::set_fullscreen( bool fs )
{
    ChimeraPtr plg = getPlugin();

    return plg->set_fullscreen( fs );
}

void JSRootAPI::toggleFullscreen()
{
    ChimeraPtr plg = getPlugin();

    plg->toggle_fullscreen();
}
