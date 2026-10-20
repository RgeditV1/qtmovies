function exec() {
  const movies = [];
  document.querySelectorAll('article.item.movies').forEach(article => {
    const tags = Array.from(article.querySelectorAll('.home_post_cat a')).map(t => ({
      name: t.innerText.trim(),
      link: t.href
    }));

    movies.push({
      id: article.id || '',
      title: article.querySelector('.in_title')?.innerText?.trim() || '',
      year: article.querySelector('.home_post_content p:nth-of-type(2)')?.innerText?.trim() || '',
      quality: article.querySelector('.squal')?.innerText?.trim() || '',
      rating: article.querySelector('.rating')?.innerText?.trim() || '',
      description: article.querySelector('.custom_synop')?.innerText?.trim() || '',
      poster: article.querySelector('img')?.src || '',
      url: article.querySelector('h3.hover_caption_caption > a')?.href || '',
      tags: tags
    });
  });

  // send data to memory to catch it with cpp
  // i dont want to create json files for it
  window.send_movie(JSON.stringify(movies));
}

exec();
