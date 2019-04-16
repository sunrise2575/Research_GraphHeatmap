# Graph2Heatmap

Graph Heatmap Visualization

## Requirement

Linux, OpenCV

## Usage

```bash
./tsv2heatmap --input=./twitter_rv.net --output=$HOME/twitter_rv.png --grid-width=16384 --brightness-increment=2
```

## Example result (Natural Graph)

### cit-Patents (Undirected)

<img src="./cit-Patents-undirected.png" width="50%" height="50%" />

### com-orkut

<img src="./com-orkut.png" width="50%" height="50%" />

## Example result (Synthetic Graph)

### graph500-scale18-ef16 (Undirected)

<img src="./graph500-scale18-ef16-undirected.png" width="50%" height="50%" />

### graph500-scale20-ef16 (Undirected)

<img src="./graph500-scale20-ef16-undirected.png" width="50%" height="50%" />

## Example result: twitter_rv.net (Brightness Increment)

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
