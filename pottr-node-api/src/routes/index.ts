import Router from "koa-router";
import { moisture } from "./moisture";
import { status } from "./status";

export const rootRouter = new Router();

rootRouter.use(status.routes());
rootRouter.use(status.allowedMethods());

rootRouter.use(moisture.routes());
rootRouter.use(moisture.allowedMethods());
