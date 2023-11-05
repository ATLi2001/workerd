#!/usr/bin/env bash

# possible architectures are linux-64, linux-arm64, darwin-64, darwin-arm64
LINUX_ARC="linux-64"
WORKERD_VERSION="1.20231002.0"
WORKERD_BIN="$HOME/workerd/bazel-bin/src/workerd/server/workerd"
WRANGLER_WORKERD_DIR="$HOME/workers-sdk/node_modules/.pnpm/@cloudflare+workerd-$LINUX_ARC@$WORKERD_VERSION/node_modules/@cloudflare/workerd-$LINUX_ARC"

# build workerd
bazel build --config=thin-lto //src/workerd/server:workerd

# remove existing binary in wrangler
rm -f "$WRANGLER_WORKERD_DIR/bin/workerd"

# copy in newly built binary
cp $WORKERD_BIN "$WRANGLER_WORKERD_DIR/bin/workerd"

