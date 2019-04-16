# Graph2Heatmap

Graph Heatmap Visualization

## Requirement

Linux, OpenCV

## Usage

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=2
```

## Example result (Brightness Increment)

Those images has quite large size. Please be relaxed for loading.

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=1
```

<img src="./twitter_rv_1.png" width="50%" height="50%" />

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=2
```

<img src="./twitter_rv_2.png" width="50%" height="50%" />

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=4
```

<img src="./twitter_rv_4.png" width="50%" height="50%" />

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=8
```

<img src="./twitter_rv_8.png" width="50%" height="50%" />

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=16
```

<img src="./twitter_rv_16.png" width="50%" height="50%" />
