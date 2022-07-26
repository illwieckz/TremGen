TremGen
=======

TremGen is a software that randomly generates maps for the free and open-source Unvanquished game. It was created for the Tremulous game before being ported to Unvanquished, hence the _TremGen_ name.

TremGen started in the year 2007 as a “_Projet de Sciences de l’Ingénieur_” (engineering science project) by some third year students at _[esiea](https://en.esiea.fr/)_ university. It was developped within a student club named _esiea-labs_ as an official school project mentored by the computer science teacher.


Initial team
------------

- _Arnaud “supernono” Deschavanne_
  - artistic contribution (textures…)
  - media and communication (interview, presentation video, he is also the music compositor of official videos)
- _Benoît “zeta” Larroque_
  - development (map props placement, shaders…)
- _Cédric “nezetic” Tessier_
  - development (map structure: terrain generation, corridors…)
- _Hubert Wassner_
  - mentoring teacher


License
-------

TremGen is covered by the [GNU General Public License version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html) or (at your option) any later version.


How-to
------

```sh
# Compile TremGen:
make

# Generate a random map:
./generate

# It will print the seed for the generated map, for example: 418018295
# You use that seed for other actions

# Build the map using the seed as argument:
./compile 418018295

# Test the map using the seed as argument:
./test 418018295

# If needed, you can regenerate the map using the seed as argument:
./generate 418018295

```


Documentation
-------------

- [official school project intermediate report by students [french/pdf]](docs/RapportMi.pdf)
- [official school project final report by students [french/pdf]](docs/RapportFinal.pdf)
- [official slides by students for final report presentation at school [french/pdf]](docs/soutenance.pdf)
- [official school project presentation by teacher to newer students for project continuation [french/pdf]](docs/Resume_et_mots_cles_du_PSI.pdf)


Some historical videos
----------------------

- [official TremGen presentation video [french/youtube]](https://www.youtube.com/watch?v=bR4Np6bmLm8)
- [official TremGen video showcasing the project with in-game footage from the LAN party played at school [french/youtube]](https://www.youtube.com/watch?v=LiqX1YRxJ1A)


Some historical web pages
-------------------------

- [sourceforge: official historical TremGen project page and repository [english]](https://sourceforge.net/projects/tremgen/)
- [esiea-labs's blog: official TremGen presentation [english/webarchive]](https://web.archive.org/web/20090415114653/http://labs.esiea.fr/en/page/49/tremgen)
- [esiea-labs's blog: official TremGen presentation [french/webarchive]](https://web.archive.org/web/20090402234049/http://labs.esiea.fr:80/fr/page/28/tremgen)
- [esiea-labs's blog: some news on TremGen [french/webarchive]](https://web.archive.org/web/20090519074645/http://labs.esiea.fr:80/fr/article/63/du-nouveau-sur-tremgen)
- [teacher's blog: official TremGen presentation [french/webarchive]](https://web.archive.org/web/20070223185344/http://professeurs.esiea.fr:80/wassner/?2007/02/13/42-renouveau-du-fps-first-person-shooter)
- [teacher's blog: some TremGen progress report [french/webarchive]](https://web.archive.org/web/20071106121342/http://professeurs.esiea.fr:80/wassner/?2007/04/01/55-le-projet-de-creation-de-map-progresse)
- [teacher's blog: announce of a LAN party at school to test TremGen [french/webarchive]](https://web.archive.org/web/20070513215458/http://professeurs.esiea.fr:80/wassner/?2007/04/17/60-lan-party-de-ce-vendredi)
- [teacher's blog: debriefing after having tested TremGen during a LAN party at school [french/webarchive]](https://web.archive.org/web/20071012185226/http://professeurs.esiea.fr:80/wassner/?2007/04/23/65-debriefing-de-la-lan-party-et-plein-d-autres-choses-encore)
- [teacher's blog: some more news about TremGen with a video [french/webarchive]](https://web.archive.org/web/20071012185017/http://professeurs.esiea.fr:80/wassner/?2007/05/12/70-derniere-video-du-projet-de-creation-de-map-pour-tremulous)
- [teacher's blog: official TremGen presentation to new students for project continuation [french/webarchive]](https://web.archive.org/web/20080125015431/http://professeurs.esiea.fr:80/wassner/?2007/11/20/100-proposition-de-projet-psi-tremgen-)
- [nezetic's developer blog: official TremGen presentation [french/webarchive]](https://web.archive.org/web/20160317004249/http://nezetic.net/projects/tremgen/)
- [lesjeuxvideos.com: an article about the project written by a student [french/webarchive]](https://web.archive.org/web/20220726162617/http://www.lesjeuxvideo.com/dossiers/maps-tremulous-gratuites-automatiques.html)
- [Tremulous forum: thread about the project [english/webarchive]](https://web.archive.org/web/20171021024248/http://tremulous.net/forum/index.php?topic=4268.0), [2nd page [english/webarchive]](https://web.archive.org/web/20171021024400/http://tremulous.net/forum/index.php?topic=4268.30)
- [Tremulous forum: another thread about the project [english/webarchive]](https://web.archive.org/web/20171021024400/http://tremulous.net/forum/index.php?topic=4268.30)
