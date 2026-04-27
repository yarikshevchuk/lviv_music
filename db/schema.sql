CREATE TABLE IF NOT EXISTS users (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  username TEXT NOT NULL UNIQUE,
  password_hash TEXT NOT NULL,
  email TEXT NOT NULL,
  age INTEGER NOT NULL,
  is_artist INTEGER NOT NULL DEFAULT 0 CHECK (is_artist IN (0, 1))
);

CREATE TABLE IF NOT EXISTS songs (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  author TEXT NOT NULL,
  duration_sec INTEGER NOT NULL DEFAULT 180,
  rating INTEGER NOT NULL DEFAULT 0,
  listen_count INTEGER NOT NULL DEFAULT 0,
  UNIQUE (name, author)
);

CREATE TABLE IF NOT EXISTS song_genres (
  song_id INTEGER NOT NULL,
  genre TEXT NOT NULL,
  PRIMARY KEY (song_id, genre),
  FOREIGN KEY (song_id) REFERENCES songs (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS playlists (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  owner_user_id INTEGER NOT NULL,
  name TEXT NOT NULL,
  description TEXT NOT NULL DEFAULT '',
  play_count INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (owner_user_id) REFERENCES users (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS playlist_songs (
  playlist_id INTEGER NOT NULL,
  song_id INTEGER NOT NULL,
  position INTEGER NOT NULL,
  PRIMARY KEY (playlist_id, song_id),
  FOREIGN KEY (playlist_id) REFERENCES playlists (id) ON DELETE CASCADE,
  FOREIGN KEY (song_id) REFERENCES songs (id) ON DELETE CASCADE
);


CREATE TABLE IF NOT EXISTS user_song_likes (
  user_id INTEGER NOT NULL,
  song_id INTEGER NOT NULL,
  PRIMARY KEY (user_id, song_id),
  FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE,
  FOREIGN KEY (song_id) REFERENCES songs (id) ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_playlists_owner ON playlists (owner_user_id);
CREATE INDEX IF NOT EXISTS idx_playlist_songs_playlist ON playlist_songs (playlist_id, position);
CREATE INDEX IF NOT EXISTS idx_likes_user ON user_song_likes (user_id);
CREATE INDEX IF NOT EXISTS idx_likes_song ON user_song_likes (song_id);
