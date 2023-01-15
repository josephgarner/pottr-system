# Vegetation Record Service

Node based vegetation recording.

The vegetation record service is a utiliy service to extend the planter-dashboard dashboard. This service will keep track of each plant in the planter box and prodive details to aid the growing and harvesting of home grown food.

#### Current MVP features

1. Save vegetation details
2. Record which plants are currently planted in each planter box

#### Technology

- Node
- Koa
- Typscript
- Mongoose
- MongoDB
- Docker

## Installation and Running

#### Install Yarn

```
npm install --global yarn
```

After cloaning this repo navigate to the folder and proceed with the following

#### Enviroment File Schema

```
DATABASE_URI=
DATABASE=
```

#### Install dependacies

```
yarn
or
yarn install
```

#### Local Development

```
yarn serve
```

#### Deploy to docker compose

```
docker-compose build

docker-compose up -d
```

## Why?

- I wanted to grow fruit and veg at home. It was brought to my attention that the ability to track the plants would aid the automation.

- All Data is stored on a local server and data owership is held by the user.

- Practice and learning
